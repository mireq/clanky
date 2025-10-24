import random

from django.core.management import BaseCommand
from model_bakery import baker

from ...models import Author, Document, Category


class Command(BaseCommand):
	def handle(self, *args, **options):
		categories = baker.make(Category, _quantity=10)
		authors = baker.make(Author, _quantity=100)
		documents = baker.make(Document, category=iter(categories * 10), _quantity=100)
		for document in documents:
			number_of_authors = random.randint(1, 5)
			document_authors = random.sample(authors, number_of_authors)
			for author in document_authors:
				document.authors.add(author)
