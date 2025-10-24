from django.db import models


class Author(models.Model):
	name = models.CharField(max_length=100)


class Category(models.Model):
	name = models.CharField(max_length=100)


class Document(models.Model):
	name = models.CharField(max_length=100)
	authors = models.ManyToManyField(Author, related_name='documents')
	category = models.ForeignKey(Category, on_delete=models.CASCADE, related_name='documents', null=True)
