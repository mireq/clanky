# -*- coding: utf-8 -*-
import argparse
import importlib
import traceback
from collections import namedtuple
from pathlib import Path

from lxml import etree, html


PUBLISHERS = [
	'linuxos_blog',
]


ArticleInfo = namedtuple('ArticleInfo', ['path', 'doc'])


def parse_article(val):
	html_path = None
	path = Path(val)
	if path.is_file():
		html_path = path
	elif path.is_dir():
		index_path = path / 'index.html'
		if index_path.is_file():
			html_path = index_path

	if html_path is None:
		raise argparse.ArgumentTypeError("No article found on path %s" % val)

	html_path = html_path.absolute()

	try:
		with open(html_path, 'r') as html_fp:
			html_doc = html.document_fromstring(html_fp.read()).getroottree()
	except Exception:
		raise argparse.ArgumentTypeError("Cannot parse %s:\n%s" % (html_path, traceback.format_exc()))

	return ArticleInfo(html_path, html_doc)


def main():
	parser = argparse.ArgumentParser(description="Publish tool")
	parser.add_argument('article', type=parse_article, help="Article directory")

	subparsers = parser.add_subparsers(help="Publisher", dest='publisher')
	subparsers.required = True

	publishers = {}
	for publisher_name in PUBLISHERS:
		publisher = importlib.import_module(f'publishers.{publisher_name}').Publisher(publisher_name)
		subparser = subparsers.add_parser(publisher_name)
		publisher.add_arguments(subparser)
		publishers[publisher_name] = publisher

	args = vars(parser.parse_args())
	publisher_name = args.pop('publisher')
	publishers[publisher_name].handle_publish(**args)


if __name__ == "__main__":
	main()
