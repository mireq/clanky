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
		self.attachments_element, self.gallery_element = self.get_library_elements()
		self.create_libraries_if_dont_exist()
		file_mapping = self.update_files()

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
				'title': self.extract_title(),
				'_continue': '1',
			}
			create_url = self.server + 'dashboard/blog/blogpost/add/'
			response = self.session.get(create_url)
			response = self.session.post(create_url, data=form_data)
			url = urlparse(response.url)
			path = url.path
			if path == '/dashboard/blog/blogpost/add/':
				raise RuntimeError("Article not created")
			article_id = re.match(r'^/dashboard/blog/blogpost/(\d+)/change/$', path).group(1)
			self.set_metadata('id', article_id, section=self.server)
		return article_id

	def extract_files(self):
		other_files = super().extract_files()
		files = {}
		body = self.article.doc.find('body/article')
		candidate = body.attrib.get('data-title-image')
		if candidate is not None:
			try:
				file_info = self.get_file_info(candidate)
				files[file_info.name] = self.get_file_info(candidate)
			except FileNotFoundError as e:
				sys.stderr.write(f"File does not exist {e.filename}\n")
			except Exception:
				traceback.print_exc()
		files.update(other_files)
		return files

	def decode_library_element(self, element) -> dict:
		return {
			'value': element.attrib['value'],
			'list_url': element.attrib['data-list-url'],
			'upload_url': element.attrib['data-upload-url'],
			'update_url': element.attrib['data-update-url'],
			'create_library_url': element.attrib['data-create-library-url'],
		}

	def get_library_elements(self):
		update_url = f'{self.server}dashboard/blog/blogpost/{self.article_id}/change/'
		response = self.session.get(update_url)
		response.raise_for_status()
		html_doc = etree.fromstring(response.text, etree.HTMLParser())
		attachments = html_doc.find('.//input[@name="attachments"]')
		gallery = html_doc.find('.//input[@name="gallery"]')
		return self.decode_library_element(attachments), self.decode_library_element(gallery)

	def create_libraries_if_dont_exist(self):
		# already exist
		if self.attachments_element['value'] and self.gallery_element['value']:
			return
		# get form
		update_url = f'{self.server}dashboard/blog/blogpost/{self.article_id}/change/'
		response = self.session.get(update_url)
		response.raise_for_status()
		html_doc = etree.fromstring(response.text, etree.HTMLParser())
		form_element = html_doc.find('.//form[@id="blogpost_form"]')

		cookies = requests.utils.dict_from_cookiejar(self.session.cookies)

		# update id values for element
		def set_id(element, val):
			element['value'] = val
			element['list_url'] = element['list_url'].replace('__library_id__', val)
			element['upload_url'] = element['upload_url'].replace('__library_id__', val)
			element['update_url'] = element['update_url'].replace('__library_id__', val)

		# create libraries
		if not self.attachments_element['value']:
			cookies = requests.utils.dict_from_cookiejar(self.session.cookies)
			form_data = {
				'csrfmiddlewaretoken': cookies['csrftoken'],
			}
			response = self.session.post(self.server + self.attachments_element['create_library_url'], data=form_data)
			response.raise_for_status()
			set_id(self.attachments_element, str(response.json()['id']))
		if not self.gallery_element['value']:
			cookies = requests.utils.dict_from_cookiejar(self.session.cookies)
			form_data = {
				'csrfmiddlewaretoken': cookies['csrftoken'],
			}
			response = self.session.post(self.server + self.gallery_element['create_library_url'], data=form_data)
			response.raise_for_status()
			set_id(self.gallery_element, str(response.json()['id']))

		cookies = requests.utils.dict_from_cookiejar(self.session.cookies)

		form_data = self.get_html_form_data(form_element)
		form_data['attachments'] = self.attachments_element['value']
		form_data['gallery'] = self.gallery_element['value']
		form_data['csrfmiddlewaretoken'] = cookies['csrftoken']

		response = self.session.post(update_url, data=form_data, allow_redirects=False)
		if response.status_code != 302:
			raise RuntimeError("Failed to create gallery")

	def update_files(self):
		uploaded_files = self.get_uploaded_fiels()
		to_delete_hashes = set(uploaded_files.keys()) - set(info.hash for info in self.files.values())

		try:
			# TODO: implement
			#self.delete_files(uploaded_files[h] for h in to_delete_hashes)
			pass
		except Exception:
			traceback.print_exc()
		for h in to_delete_hashes:
			del uploaded_files[h]

		to_upload_files = [info for info in self.files.values() if not info.hash in uploaded_files]
		try:
			uploaded_files.update(self.upload_files(to_upload_files))
		except Exception:
			traceback.print_exc()
		self.set_metadata('uploads', json.dumps(uploaded_files), section=self.server)

		file_mapping = []
		for info in self.files.values():
			uploaded = uploaded_files.get(info.hash)
			if uploaded is not None:
				file_mapping.append([info, uploaded])
		return file_mapping

	def upload_files(self, files):
		files = list(files)
		if not files:
			return {}

		upload_metadata = {}
		return upload_metadata
