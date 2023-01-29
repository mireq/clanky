# -*- coding: utf-8 -*-
from urllib.parse import urlparse

import requests
from lxml import html


class BaseDownloader(object):
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
