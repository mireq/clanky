# -*- coding: utf-8 -*-
from .base import BaseDownloader

# https://eu-central-1.linodeobjects.com/wisdomtech/media/filer_public_thumbnails/filer_public/66/7d/667d69dd-d314-4753-97eb-813ebfc549cb/pisanie_ciarok.png__1600x1100_subsampling-2.png
# https://eu-central-1.linodeobjects.com/wisdomtech/media/filer_public/66/7d/667d69dd-d314-4753-97eb-813ebfc549cb/pisanie_ciarok.png


class Downloader(BaseDownloader):
	ARTICLE_XPATH = 'body/main/div[@class="main-text"]'

	def parse_main_document(self):
		doc = super().parse_main_document()
		sharer = doc.find('.//div[@class="share"]')
		if sharer is not None:
			sharer.getparent().remove(sharer)
		return doc
