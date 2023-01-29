#!/usr/bin/env python
# -*- coding: utf-8 -*-
import argparse
import importlib
from pathlib import Path


DOWNLOADERS = [
	'wisdom_blog',
]


def main():
	parser = argparse.ArgumentParser(description="Publish tool")
	parser.add_argument('article_directory', type=str, help="Article directory")
	parser.add_argument('url', type=str, help="Article URL")

	subparsers = parser.add_subparsers(help="Downloader", dest='downloader')
	subparsers.required = True

	downloaders = {}
	for downloader_name in DOWNLOADERS:
		downloader = importlib.import_module(f'downloaders.{downloader_name}').Downloader(downloader_name)
		subparser = subparsers.add_parser(downloader_name)
		downloader.add_arguments(subparser)
		downloaders[downloader_name] = downloader

	args = vars(parser.parse_args())
	args['article_directory'] = Path(args['article_directory'])
	args['article_directory'].mkdir(parents=True, exist_ok=True)
	args['files_directory'] = args['article_directory'] / 'files'
	args['files_directory'].mkdir(parents=True, exist_ok=True)
	downloader_name = args.pop('downloader')
	downloaders[downloader_name].handle_download(**args)



if __name__ == "__main__":
	main()
