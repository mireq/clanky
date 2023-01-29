# -*- coding: utf-8 -*-
from .base import BaseDownloader

# https://eu-central-1.linodeobjects.com/wisdomtech/media/filer_public_thumbnails/filer_public/66/7d/667d69dd-d314-4753-97eb-813ebfc549cb/pisanie_ciarok.png__1600x1100_subsampling-2.png
# https://eu-central-1.linodeobjects.com/wisdomtech/media/filer_public/66/7d/667d69dd-d314-4753-97eb-813ebfc549cb/pisanie_ciarok.png


class Downloader(BaseDownloader):
	ARTICLE_XPATH = 'body/main/div[@class="main-text"]'
	WEB_PREFIX = 'https://www.wisdomtech.sk'

	def parse_main_document(self):
		doc = super().parse_main_document()
		sharer = doc.find('.//div[@class="share"]')
		if sharer is not None:
			sharer.getparent().remove(sharer)
		return doc

	def preprocess_link_response(self, link, response):
		link = super().preprocess_link_response(link, response)
		if link is not None and link.startswith(self.WEB_PREFIX):
			return link[len(self.WEB_PREFIX):]
