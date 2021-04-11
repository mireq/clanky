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
	server = None
	article_id = None
	blog_name = None

	def add_arguments(self, parser):
		parser.add_argument('--server', default='https://linuxos.sk/')

	def publish(self, server):
		self.server = server
		self.load_cookies(section=server)
		self.do_login()
		self.article_id = self.get_or_create_article_id()
		file_mapping = self.update_files()
		self.article_replace_links((src.name, dest[1]) for src, dest in file_mapping)
		self.update_article()

	def get_login(self):
		return input("Login: ")

	def get_password(self):
		return getpass()

	def find_blog_name(self):
		response = self.session.get(self.server + 'profil/ja/')
		url = urlparse(response.url)
		if url.path == '/profil/ja/':
			html_doc = etree.fromstring(response.text, etree.HTMLParser())
			link = html_doc.xpath('.//a[text()=\'Zobraziť všetky blogy\']')
			if len(link) == 0:
				raise RuntimeError("Blog not found")
			return link[0].attrib['href'].split('/')[-3]

	def send_login_form(self, login, password):
		login_url = self.server + 'prihlasit/login/'
		self.session.get(login_url)
		cookies = requests.utils.dict_from_cookiejar(self.session.cookies)
		form_data = {
			'csrfmiddlewaretoken': cookies['csrftoken'],
			'login': login,
			'password': password,
			'remember': 'on',
		}
		response = self.session.post(login_url, data=form_data)
		url = urlparse(response.url)
		return url.path != '/prihlasit/login/'

	def do_login(self):
		self.blog_name = self.find_blog_name()
		if not self.blog_name:
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

	def get_or_create_article_id(self):
		article_id = self.get_metadata('id', section=self.server)
		if article_id is None:
			cookies = requests.utils.dict_from_cookiejar(self.session.cookies)
			form_data = {
				'csrfmiddlewaretoken': cookies['csrftoken'],
				'title': self.extract_title(),
				'original_perex': 'draft',
				'original_perex_format': 'html',
				'original_content': 'draft',
				'original_content_format': 'html',
				'create': '1',
				'pub_time': '01.01.2100 00:00:00',
			}
			create_url = self.server + 'blog/admin/create-post/'
			response = self.session.get(create_url)
			response = self.session.post(create_url, data=form_data)
			url = urlparse(response.url)
			path = url.path
			article_id = re.match(r'^.*/([^/]*)/$', path).group(1)
			self.set_metadata('id', article_id, section=self.server)
		return article_id

	def get_uploaded_fiels(self):
		uploads = self.get_metadata('uploads', section=self.server)
		if not uploads:
			return {}
		return json.loads(uploads)

	def update_files(self):
		uploaded_files = self.get_uploaded_fiels()
		to_delete_hashes = set(uploaded_files.keys()) - set(info.hash for info in self.files.values())
		try:
			self.delete_files(uploaded_files[h] for h in to_delete_hashes)
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

	def delete_files(self, files):
		attachments_url = f'{self.server}blog/{self.blog_name}/update/{self.article_id}/attachments/'
		files = list(files)

		if len(files) == 0:
			return

		delete_ids = set(info[0] for info in files)

		response = self.session.get(attachments_url, allow_redirects=False)
		if response.status_code != 200:
			raise RuntimeError(f"Wrong status code {response.status_code} for url {attachments_url}")

		html_doc = etree.fromstring(response.content, etree.HTMLParser())
		upload_form = html_doc.find('.//div[@id="main_content"]//form')
		form_data = self.get_html_form_data(upload_form)
		form_data.pop('attachment')

		for i in range(1000):
			key = f'form-{i}-id'
			if not key in form_data:
				break
			image_id = form_data[key]
			if image_id in delete_ids:
				form_data[f'form-{i}-DELETE'] = 'on'

		response = self.session.post(attachments_url, data=form_data)
		response.raise_for_status()

	def get_image_ids(self, form_data):
		image_ids = set()
		for i in range(1000):
			key = f'form-{i}-id'
			if not key in form_data:
				break
			image_ids.add(form_data[key])
		return image_ids

	def upload_files(self, files):
		files = list(files)
		if not files:
			return {}

		attachments_url = f'{self.server}blog/{self.blog_name}/update/{self.article_id}/attachments/'
		response = self.session.get(attachments_url, allow_redirects=False)
		response.raise_for_status()
		if response.status_code != 200:
			raise RuntimeError(f"Wrong status code {response.status_code} for url {attachments_url}")

		html_doc = etree.fromstring(response.content, etree.HTMLParser())
		upload_form = html_doc.find('.//div[@id="main_content"]//form')
		form_data = self.get_html_form_data(upload_form)
		form_data.pop('attachment')

		current_image_ids = self.get_image_ids(form_data)

		uploads = []
		for info in files:
			with open(info.path, 'rb') as fp:
				uploads.append((info.path.name, fp.read()))

		uploads = [('attachment', upload) for upload in uploads]
		response = self.session.post(attachments_url, data=form_data, files=uploads)
		html_doc = etree.fromstring(response.content, etree.HTMLParser())
		upload_form = html_doc.find('.//div[@id="main_content"]//form')
		form_data = self.get_html_form_data(upload_form)
		new_image_ids = self.get_image_ids(form_data)

		upload_metadata = {}

		uploaded_ids = sorted(int(pk) for pk in (new_image_ids - current_image_ids))
		for info, new_id in zip(files, uploaded_ids):
			id_input = upload_form.find(f'.//input[@type="hidden"][@value="{new_id}"]')
			file_url = id_input.getparent().getparent().find(".//a").attrib['href']
			upload_metadata[info.hash] = [str(new_id), file_url]

		return upload_metadata

	def update_article(self):
		update_url = f'{self.server}blog/{self.blog_name}/update/{self.article_id}/'
		response = self.session.get(update_url, allow_redirects=False)
		response.raise_for_status()
		if response.status_code != 200:
			raise RuntimeError(f"Wrong status code {response.status_code} for url {attachments_url}")

		html_doc = etree.fromstring(response.content, etree.HTMLParser())
		article_form = html_doc.find('.//div[@id="main_content"]//form')
		form_data = self.get_html_form_data(article_form)
		form_data['title'] = self.extract_title()
		form_data['original_perex'] = self.extract_perex(as_string=True)
		form_data['original_content'] = self.extract_content(as_string=True)
		form_data['update'] = '1'

		response = self.session.post(update_url, data=form_data, allow_redirects=False)
		response.raise_for_status()
		if response.status_code == 200:
			debug_file = "/tmp/out.html"
			with open(debug_file, 'w') as fp:
				fp.write(response.text)
			raise RuntimeError(f"Wrong data, check {debug_file}")
