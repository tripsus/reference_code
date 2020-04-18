from __future__ import absolute_import, unicode_literals
import os
from celery import Celery

# set the default Django settings module for the 'celery' program.
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'django_celery.settings')

test_celery_app = Celery('django_celery',
             broker='pyamqp://guest@localhost//',
             backend='redis://localhost:6379/14',
            )
test_celery_app.conf.broker_transport_options = {'visibility_timeout': 10}

'''
 To route tasks to different queues we can use static settings like
 app.conf.task_routes = {'celery_tasks.tasks.add': {'queue': 'test'}}
 or we can explicitly pass name of queue in apply_async method while adding
 tasks.
'''

"""
Tasks will be acknowledged only after it is completed. By default celery
acknowledges tasks when it pick it from rabbitmq
"""
CELERY_TASK_ACKS_LATE = True
# Using a string here means the worker doesn't have to serialize
# the configuration object to child processes.
# - namespace='CELERY' means all celery-related configuration keys
#   should have a `CELERY_` prefix.
test_celery_app.config_from_object('django.conf:settings', namespace='CELERY')

# Load task modules from all registered Django app configs.
test_celery_app.autodiscover_tasks()


@test_celery_app.task(bind=True)
def debug_task(self):
    print('Request: {0!r}'.format(self.request))