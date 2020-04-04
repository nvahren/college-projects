# Nathan Vahrenberg
# CSE30332 Programming Paradigms
# CherryPy Primer
# 4 March 2016

import sys
sys.path.append('/afs/nd.edu/user37/cmc/Public/paradigms/python/local/lib/python2.6/site-packages/requests-2.0.0-py2.6.egg')

import cherrypy
from dcont import DictionaryController
import re, json

def start_service():
	dispatcher = cherrypy.dispatch.RoutesDispatcher()
	
	# set routes
	dispatcher.connect('dict_get', '/dictionary/:key', controller=DictionaryController, action = 'GET', conditions=dict(method=['GET']))
	dispatcher.connect('dict_get', '/dictionary/', controller=DictionaryController, action = 'GET_INDEX', conditions=dict(method=['GET']))
	dispatcher.connect('dict_put', '/dictionary/:key', controller=DictionaryController, action = 'PUT', conditions=dict(method=['PUT']))
	dispatcher.connect('dict_post', '/dictionary/', controller=DictionaryController, action = 'POST', conditions=dict(method=['POST']))
	dispatcher.connect('dict_delete', '/dictionary/:key', controller=DictionaryController, action = 'DELETE', conditions=dict(method=['DELETE']))
	dispatcher.connect('dict_delete_all', '/dictionary/', controller=DictionaryController, action = 'DELETE_ALL', conditions=dict(method=['DELETE']))
	conf = { 'global' : {'server.socket_host' : '127.0.0.1', 'server.socket_port': 40042,}, '/' : {'request.dispatch':dispatcher,} }
	
	# update and start server
	cherrypy.config.update(conf)
	app = cherrypy.tree.mount(None, config=conf)
	cherrypy.quickstart(app)

if __name__ == '__main__':
	DictionaryController = DictionaryController()
	start_service()
