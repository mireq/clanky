# -*- coding: utf-8 -*-
import re

from .base import BaseDownloader
import datetime


THUMBNAIL_RX = re.compile(f'^{re.escape("https://eu-central-1.linodeobjects.com/wisdomtech/media/filer_public_thumbnails/")}(.*)__[0-9.]+x[0-9.]+.*$')


class Downloader(BaseDownloader):
	ARTICLE_XPATH = 'body/main/div[@class="main-text"]'
	WEB_PREFIX = 'https://www.wisdomtech.sk'

	def parse_main_document(self):
		doc = super().parse_main_document()
		sharer = doc.find('.//div[@class="share"]')
		if sharer is not None:
			sharer.getparent().remove(sharer)
		return doc

	def download_link(self, link):
		match = THUMBNAIL_RX.match(link)
		if match:
			link = f'https://eu-central-1.linodeobjects.com/wisdomtech/media/{match.group(1)}'
		return super().download_link(link)

	def extract_title(self, tree):
		return tree.find('.//h1').text

	def extract_perex(self, tree):
		header = tree.find('.//div[@class="blog-header"]')
		return [child for child in header.getchildren() if child.attrib.get('class') != 'img']

	def extract_content(self, tree):
		header = tree.find('.//div[@class="main-text"]')
		return list(header.getchildren())

	def write_contents(self, output_document, input_document):
		super().write_contents(output_document, input_document)

		title = input_document.find('./head/title')
		title = '' if title is None else title.text
		title = re.sub(r'^Blog \| ', '', title)
		title = re.sub(r' \| Wisdom Technologies$', '', title)

		article = output_document.find('.//article')
		article.attrib['data-page-title'] = title

		info = input_document.find('.//main/div[@class="leading"]/div[@class="info"]').text
		info = re.sub(r'\s+/.*', '', info)

		months = [
			'január',
			'február',
			'marec',
			'apríl',
			'máj',
			'jún',
			'júl',
			'august',
			'september',
			'október',
			'november',
			'december',
		]

		for month, text in enumerate(months, 1):
			info = info.replace(text, str(month))

		article_date = datetime.datetime.strptime(info, '%d. %m %Y')

		article.attrib['data-pub-time'] = article_date.strftime('%Y-%m-%d')
