# -*- coding: utf-8 -*-
class BaseDownloader(object):
	def __init__(self, name):
		self.name = name

	def add_arguments(self, parser):
		pass

	def handle_download(self, **args):
		print(args)
