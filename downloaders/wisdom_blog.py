# -*- coding: utf-8 -*-
import re

from .base import BaseDownloader


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
