# -*- coding: utf-8 -*-
from urllib.parse import urlparse

import logging
import requests
from lxml import html
from typing import Set, Dict
from hashlib import md5


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

	def add_arguments(self, parser):
		pass

	@property
	def parsed_url(self):
		return urlparse(self.kwargs['url'])

	def handle_download(self, **kwargs):
		self.kwargs = kwargs
		self.main_document = self.download_main_document()
		self.main_document_tree = self.parse_main_document()
		self.files = self.load_existing_files()
		self.links = self.extract_links()
		self.files.update(self.download_links(self.links))

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

	def load_existing_files(self) -> Dict[bytes, str]:
		files = {}
		for entry in self.kwargs['files_directory'].iterdir():
			if not entry.is_file():
				continue
			with entry.open('rb') as fp:
				files[md5(fp.read()).digest()] = entry
		return files

	def download_links(self, links: Set[str]) -> Dict[bytes, str]:
		files = {}
		for link in links:
			try:
				print(link)
			except Exception:
				logger.exception("Failed to download link %s", link)
		return files
