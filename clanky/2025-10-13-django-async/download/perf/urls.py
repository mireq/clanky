from django.urls import path
from . import views

urlpatterns = [
	path('naive/sync/', views.naive_sync),
	path('naive/async/', views.naive_async),
	path('db/sync/', views.db_sync),
	path('db/async/', views.db_async),
	path('db-opt/sync/', views.db_opt_sync),
	path('db-opt/async/', views.db_opt_async),
]
