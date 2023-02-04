# -*- coding: utf-8 -*-
from .base import BasePublisher
from getpass import getpass
from urllib.parse import urlparse
import sys
import requests
import re
import json
import traceback
from lxml import etree


class Publisher(BasePublisher):
	def add_arguments(self, parser):
		parser.add_argument('--server', default='https://blog.wisdomtech.sk/')

	def publish(self, server):
		self.server = server
		self.session.headers['Referer'] = server
		self.load_cookies(section=server)
		self.do_login()
		self.article_id = self.get_or_create_article_id()
		print(self.article_id)

	def is_logged(self):
		response = self.session.get(self.server + 'dashboard/blog/blogpost/')
		url = urlparse(response.url)
		return url.path == '/dashboard/blog/blogpost/'

	def get_login(self):
		return input("Login: ")

	def get_password(self):
		return getpass()

	def do_login(self):
		# try open admin interface
		if not self.is_logged():
			config_login = self.get_config('login', section=self.server)
			login = config_login
			if login is None:
				login = self.get_login()
			else:
				sys.stdout.write("Login: %s\n" % login)

			while True:
				password = self.get_password()
				if self.send_login_form(login, password):
					break
				else:
					sys.stdout.write("Wrong password\n")
				login = self.get_login()

			if login != config_login:
				self.set_config('login', login, section=self.server)


		self.write_cookies(section=self.server)

	def send_login_form(self, login, password):
		login_url = self.server + 'dashboard/login/'
		self.session.get(login_url)
		cookies = requests.utils.dict_from_cookiejar(self.session.cookies)
		form_data = {
			'csrfmiddlewaretoken': cookies['csrftoken'],
			'username': login,
			'password': password,
		}
		response = self.session.post(login_url, data=form_data)
		url = urlparse(response.url)
		return url.path != '/dashboard/login/'

	def get_or_create_article_id(self):
		article_id = self.get_metadata('id', section=self.server)
		if article_id is None:
			cookies = requests.utils.dict_from_cookiejar(self.session.cookies)
			form_data = {
				'csrfmiddlewaretoken': cookies['csrftoken'],
				'sk': '',
				'title': 'draft',
				'_continue': '1',
			}
			create_url = self.server + 'dashboard/blog/blogpost/add/'
			response = self.session.get(create_url)
			response = self.session.post(create_url, data=form_data)
			url = urlparse(response.url)
			path = url.path
			print(path)
			if path == '/dashboard/blog/blogpost/add/':
				raise RuntimeError("Article not created")
			article_id = re.match(r'^/dashboard/blog/blogpost/(\d+)/change/$', path).group(1)
			self.set_metadata('id', article_id, section=self.server)
		return article_id
