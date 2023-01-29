# -*- coding: utf-8 -*-
from urllib.parse import urlparse
import requests



class BaseDownloader(object):
	def __init__(self, name):
		self.name = name
		self.kwargs = {}
		self.main_document = ''

	def add_arguments(self, parser):
		pass

	@property
	def parsed_url(self):
		return urlparse(self.kwargs['url'])

	def handle_download(self, **kwargs):
		self.kwargs = kwargs
		self.main_document = self.download_main_document()

	def download_main_document(self):
		req = requests.get(self.kwargs['url'])
		req.raise_for_status()
		return req.text
