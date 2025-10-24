from asgiref.sync import sync_to_async
from django.http.response import JsonResponse
from .models import Document


def naive_sync(request):
	return JsonResponse({"status": "ok"})


async def naive_async(request):
	return JsonResponse({"status": "ok"})


def db_sync(request):
	data = []
	for document in Document.objects.order_by('pk'):
		authors = []
		data.append(
			{
				"name": document.name,
				"category": document.category.name,
				"authors": authors,
			}
		)
		for author in document.authors.all():
			authors.append({"name": author.name})
	return JsonResponse({"data": data})


async def db_async(request):
	data = []
	async for document in Document.objects.order_by('pk'):
		authors = []
		data.append(
			{
				"name": document.name,
				"category": (await sync_to_async(getattr)(document, 'category')).name,
				"authors": authors,
			}
		)
		async for author in document.authors.all():
			authors.append({"name": author.name})
	return JsonResponse({"data": data})


def db_opt_sync(request):
	data = []
	for document in Document.objects.order_by('pk').prefetch_related('authors').select_related('category'):
		authors = []
		data.append(
			{
				"name": document.name,
				"category": document.category.name,
				"authors": authors,
			}
		)
		for author in document.authors.all():
			authors.append({"name": author.name})
	return JsonResponse({"data": data})


async def db_opt_async(request):
	data = []
	async for document in Document.objects.order_by('pk').prefetch_related('authors').select_related('category'):
		authors = []
		data.append(
			{
				"name": document.name,
				"category": (await sync_to_async(getattr)(document, 'category')).name,
				"authors": authors,
			}
		)
		async for author in document.authors.all():
			authors.append({"name": author.name})
	return JsonResponse({"data": data})
