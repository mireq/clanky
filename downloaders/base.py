# -*- coding: utf-8 -*-
import logging
import mimetypes
import os
from hashlib import md5
from typing import Set, Dict
from urllib.parse import urlparse

import requests
from lxml import html, etree


logger = logging.getLogger(__name__)


ARTICLE_TEMPLATE = """<!DOCTYPE html>
<html>
<head>
	<title></title>
	<meta charset="utf-8" />
	<link href="../../../common/style.css" rel="stylesheet" />
</head>
<body>
<article>

<header>
	<h1></h1>
</header>

</article>
<script src="../../../common/script.js"></script>
</body>
</html>
"""



class DownloadError(RuntimeError):
	pass


class BaseDownloader(object):
	LINK_ATTRS = {'href', 'src'}
	ARTICLE_XPATH = 'body/main'

	def __init__(self, name):
		self.name = name
		self.kwargs = {}
		self.main_document = ''
		self.main_document_tree = None
		self.links = set()
		self.link_replacements = {}

	def add_arguments(self, parser):
		pass

	@property
	def parsed_url(self):
		return urlparse(self.kwargs['url'])

	def handle_download(self, **kwargs):
		self.kwargs = kwargs
		self.main_document = self.download_main_document()
		self.main_document_tree = self.parse_main_document()
		self.links = self.extract_links()
		self.link_replacements = self.download_links(self.links)
		self.reqplace_links(self.main_document_tree, self.link_replacements)
		self.write_article()

	def download_main_document(self):
		req = requests.get(self.kwargs['url'])
		req.raise_for_status()
		return req.text

	def parse_main_document(self):
		tree = html.fromstring(self.main_document)
		base_url = None
		basetags = tree.xpath('//base[@href]|//x:base[@href]', namespaces={'x': html.XHTML_NAMESPACE})
		for b in basetags:
			base_url = b.get('href')
		if base_url is None:
			base_url = self.kwargs['url']
		tree = html.fromstring(self.main_document, base_url=base_url)
		tree.make_links_absolute()
		return tree

	def extract_links(self):
		main_content = self.main_document_tree.find(self.ARTICLE_XPATH)
		if main_content is None:
			raise DownloadError(f"Element {self.ARTICLE_XPATH} not found")
		candidates = set()
		candidates |= self.find_links_from_content(main_content)
		return candidates

	def find_links_from_content(self, fragment) -> Set[str]:
		links = set()
		for attr in self.LINK_ATTRS:
			links |= set(element.attrib[attr] for element in fragment.iterfind(f'.//*[@{attr}]'))
		return links

	def hash_file(self, file) -> bytes:
		if isinstance(file, bytes):
			return md5(file).digest()
		else:
			with open(file, 'rb') as fp:
				return md5(fp.read()).digest()

	def download_links(self, links: Set[str]) -> Dict[str, str]:
		link_replacements = {}

		file_names = set()
		def generate_unique_name(name):
			base_name = name
			i = 1
			while name in file_names:
				name = list(os.path.splitext(base_name))
				name[0] = f'{name[0]}_{i}'
				name = ''.join(name)
				i += 1
			file_names.add(name)
			return name

		for link in links:
			try:
				response = self.download_link(link)
				#response.raise_for_status()
				content_type = response.headers.get('Content-Type', '').split(';')[0].strip()
				new_link = self.preprocess_link_response(link, response)
				if new_link is not None:
					continue
				response_data = response.raw.read()
				filename = link
				filename.rstrip('/')
				filename = filename.split('/')[-1]
				expected_ext = mimetypes.guess_extension(content_type)
				if expected_ext is not None:
					filename, __ = os.path.splitext(filename)
					filename = f'{filename}{expected_ext}'
				filename = generate_unique_name(filename)
				with (self.kwargs['files_directory'] / filename).open('wb') as fp:
					fp.write(response_data)
				link_replacements[link] = os.path.join('files', filename)
			except Exception:
				logger.exception("Failed to download link %s", link)

		return link_replacements

	def preprocess_link_response(self, link, response):
		content_type = response.headers.get('Content-Type', '').split(';')[0].strip()
		if content_type == 'text/html':
			return link

	def download_link(self, link):
		return requests.get(link, stream=True)

	def reqplace_links(self, tree, link_replacements):
		for attr in self.LINK_ATTRS:
			for element in tree.iterfind(f'.//*[@{attr}]'):
				val = element.attrib[attr]
				element.attrib[attr] = link_replacements.get(val, val)

	def extract_title(self, tree):
		title = tree.find('./head/title')
		if title is not None:
			return title.text
		return ''

	def extract_perex(self, tree): # pylint: disable=unused-argument
		return []

	def extract_content(self, tree): # pylint: disable=unused-argument
		return []

	def write_contents(self, output_document, input_document):
		article = output_document.find('.//article')
		perex = output_document.find('.//header')
		title = output_document.find('.//h1')
		head_title = output_document.find('.//title')
		title.text = self.extract_title(input_document)
		for fragment in self.extract_perex(input_document):
			perex.append(fragment)
		head_title.text = self.extract_title(input_document)
		for fragment in self.extract_content(input_document):
			article.append(fragment)

	def write_article(self):
		output = html.fromstring(ARTICLE_TEMPLATE)
		self.write_contents(output, self.main_document_tree)
		with (self.kwargs['article_directory'] / 'index.html').open('wb') as fp:
			fp.write(etree.tostring(output, doctype='<!DOCTYPE html>', method='html', encoding='utf-8'))
