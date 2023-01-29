# -*- coding: utf-8 -*-
import logging
import mimetypes
import os
from hashlib import md5
from typing import Set, Dict
from urllib.parse import urlparse

import requests
from lxml import html


logger = logging.getLogger(__name__)


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
		self.download_links(self.links)

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
				response = requests.get(link, stream=True)
				#response.raise_for_status()
				content_type = response.headers.get('Content-Type', '').split(';')[0].strip()
				new_link = self.preprocess_link_response(link, response)
				if new_link is not None:
					print("new link", new_link)
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
			except Exception:
				logger.exception("Failed to download link %s", link)

		return link_replacements

	def preprocess_link_response(self, link, response):
		content_type = response.headers.get('Content-Type', '').split(';')[0].strip()
		print(link)
		if content_type == 'text/html':
			return link
