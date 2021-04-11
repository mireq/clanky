# -*- coding: utf-8 -*-
import base64
import configparser
import hashlib
import os
import sys
import traceback
from copy import deepcopy
from collections import Counter, namedtuple, defaultdict
from http.cookiejar import LWPCookieJar
from io import StringIO
from pathlib import Path

import requests
from lxml import etree


ARTICLE_CONFIG_FILE = 'article_config.ini'


class NO_VALUE:
	pass


def get_config_dir():
	xdg_config_home = os.getenv("XDG_CONFIG_HOME")
	if xdg_config_home:
		return Path(xdg_config_home)
	else:
		return Path.home() / '.config'


FileInfo = namedtuple('FileInfo', ['name', 'hash', 'path'])


class BasePublisher(object):
	article = None

	def __init__(self, name):
		self.name = name
		self._config = configparser.ConfigParser()
		self._config.path = get_config_dir() / ARTICLE_CONFIG_FILE
		self._config.read(self._config.path)
		self._metadata = configparser.ConfigParser()
		self._files_by_name = {}
		self.session = requests.Session()
		self.session.cookies = LWPCookieJar()

	def add_arguments(self, parser): # pylint: disable=unused-argument
		pass

	def publish(self, **options):
		raise NotImplementedError()

	def handle_publish(self, article, **options):
		self.article = article
		self.cleanup_code()
		self.__load_metadata()
		self.__extract_files()
		self.replace_counters()
		self.replace_footnotes()
		self.publish(**options)

	def __get_full_section(self, section=None):
		full_section = self.name
		if section is not None:
			full_section = f'{full_section}:{section}'
		return full_section

	def get_config(self, option, section=None, default=None, return_type=None):
		return self.__get_config(self._config, option, section, default, return_type)

	def remove_config(self, option, section=None):
		return self.__remove_config(self._config, option, section)

	def set_config(self, option, value, section=None):
		return self.__set_config(self._config, option, value, section)

	def __get_config(self, config, option, section=None, default=None, return_type=None):
		section = self.__get_full_section(section)
		if return_type is None:
			return config.get(section, option, fallback=default)
		elif return_type is int:
			return config.getint(section, option, fallback=default)
		elif return_type is float:
			return config.getfloat(section, option, fallback=default)
		elif return_type is bool:
			return config.getbool(section, option, fallback=default)
		else:
			raise ValueError("Unsupported return type: %s" % return_type)

	def __remove_config(self, config, option, section=None):
		section = self.__get_full_section(section)
		config.remove_option(section, option)

	def __set_config(self, config, option, value, section=None):
		section = self.__get_full_section(section)
		if not config.has_section(section):
			config.add_section(section)
		config.set(section, option, str(value))
		with open(config.path, 'w') as fp:
			config.write(fp)

	def write_cookies(self, section=None):
		cookie_data = self.session.cookies.as_lwp_str()
		self.set_config('_cookies', base64.b64encode(cookie_data.encode('utf-8')).decode('ascii'), section=section)

	def load_cookies(self, section=None):
		self.session.cookies = LWPCookieJar()
		cookie_data = self.get_config('_cookies', section=section)
		if not cookie_data:
			return
		cookie_data = base64.b64decode(cookie_data.encode('ascii')).decode('utf-8')
		cookie_fp = StringIO()
		cookie_fp.write("#LWP-Cookies-2.0\n")
		cookie_fp.write(cookie_data)
		cookie_fp.seek(0)
		self.session.cookies._really_load(cookie_fp, '', False, False)

	def __load_metadata(self):
		path = self.article.path.parent / 'metadata.ini'
		self._metadata.path = path
		self._metadata.read(path)

	def get_metadata(self, option, section=None, default=None, return_type=None):
		return self.__get_config(self._metadata, option, section, default, return_type)

	def remove_metadata(self, option, section=None):
		return self.__remove_config(self._metadata, option, section)

	def set_metadata(self, option, value, section=None):
		return self.__set_config(self._metadata, option, value, section)

	def __extract_files(self):
		self._files_by_name = {}
		is_local = lambda val: not ('://' in val or val.startswith('/'))
		body = self.article.doc.find('body/article')
		candidates = set()
		candidates |= set(element.attrib['src'] for element in body.iterfind('.//*[@src]'))
		candidates |= set(element.attrib['href'] for element in body.iterfind('.//*[@href]'))
		candidates = set(candidate for candidate in candidates if is_local(candidate))
		for candidate in candidates:
			try:
				file_info = self.__get_file_info(candidate)
			except FileNotFoundError as e:
				sys.stderr.write(f"File does not exist {e.filename}\n")
				continue
			except Exception:
				traceback.print_exc()
				continue
			self._files_by_name[file_info.name] = file_info

	def __get_file_info(self, filename):
		path = (self.article.path.parent / Path(filename)).absolute()
		with open(path, 'rb') as fp:
			file_hash = hashlib.sha224(fp.read()).hexdigest()
		return FileInfo(filename, file_hash, path)

	@property
	def files(self):
		return self._files_by_name

	def get_html_form_data(self, form):
		html_data = {}
		for field in form.xpath('.//*[self::textarea or self::select or self::input]'):
			name = field.attrib.get('name', None)
			if name is None:
				continue
			if field.tag == 'input':
				if field.attrib.get('type') in ('checkbox', 'radio'):
					if 'checked' in field.attrib:
						html_data[name] = field.attrib.get('value', '')
				else:
					html_data[name] = field.attrib.get('value', '')
			elif field.tag == 'textarea':
				html_data[name] = field.text
			elif field.tag == 'select':
				html_data[name] = ''
		return html_data

	def article_replace_links(self, mapping):
		body = self.article.doc.find('body/article')

		src_elements = defaultdict(list)
		href_elements = defaultdict(list)
		for element in body.iterfind('.//*[@src]'):
			src_elements[element.attrib['src']].append(element)
		for element in body.iterfind('.//*[@href]'):
			href_elements[element.attrib['href']].append(element)

		for src, dest in mapping:
			for element in src_elements[src]:
				element.attrib['src'] = dest
			for element in href_elements[src]:
				element.attrib['href'] = dest

	def cleanup_code(self):
		body = self.article.doc.find('body/article')
		for script in body.findall('.//script'):
			script.getparent().remove(script)

	def replace_counters(self):
		counter = Counter()
		elements = self.article.doc.findall('/body/article//counter')
		for element in elements:
			name = element.attrib.get('name', 'default')
			cnt = counter[name] + 1
			counter[name] = cnt
			element.tail = str(cnt) + element.tail if element.tail else str(cnt)
		etree.strip_elements(self.article.doc, 'counter', with_tail=False)

	def replace_footnotes(self):
		body = self.article.doc.find('body/article')

		elements = body.findall('.//foot-note')
		for i, element in enumerate(elements):
			name = element.attrib.get('name', 'undefined')
			sub = etree.Element("sup")
			link = etree.SubElement(sub, "a", id=f"fn-{name}", href=f"#footnote-{name}")
			link.text = f"[{i+1}]"
			element.addnext(sub)

		etree.strip_elements(self.article.doc, 'foot-note', with_tail=False)

		if elements:
			header = etree.SubElement(body, "h2")
			header.text = "Poznámky"
			header.tail = "\n\n"

			ol = etree.SubElement(body, "ol")
			ol.attrib['class'] = 'footnotes'
			ol.tail = "\n\n"

			for element in elements:
				li = deepcopy(element)
				name = element.attrib.get('name', 'undefined')
				if 'name' in li.attrib:
					del li.attrib['name']
				li.tag = 'li'
				li.attrib['id'] = f'footnote-{name}'
				ol.append(li)

	def extract_title(self):
		return self.article.doc.find(".//title").text

	def extract_perex(self, as_string=False):
		header = self.article.doc.find('.//header')
		if header is None:
			header = etree.Element('header')
		else:
			header = deepcopy(header)
			header.tail = None
		etree.strip_elements(header, 'h1', with_tail=False)
		if as_string:
			text = etree.tostring(header, encoding='unicode')
			text = text[len('<'+header.tag+'>'):-len('</'+header.tag+'>')]
			return text.strip()
		else:
			return header

	def extract_content(self, as_string=False):
		article = etree.Element('article')
		body = self.article.doc.find('body/article')
		article.text = body.text
		for child in body:
			article.append(deepcopy(child))
		etree.strip_elements(article, 'header', with_tail=False)
		if as_string:
			text = etree.tostring(article, encoding='unicode')
			text = text[len('<'+article.tag+'>'):-len('</'+article.tag+'>')]
			return text.strip()
		else:
			return article
