# Nathan Vahrenberg
# CSE30332 Programming Paradigms
# AJAX
# 8 April 2016

import sys
sys.path.append('/afs/nd.edu/user37/cmc/Public/paradigms/python/local/lib/python2.6/site-packages/requests-2.0.0-py2.6.egg')

import cherrypy
from mcont import MovieController
import re, json

class OptionsController:
        def OPTIONS(self, *args, **kwargs):
                return ""

def CORS():
    cherrypy.response.headers["Access-Control-Allow-Origin"] = "*"
    cherrypy.response.headers["Access-Control-Allow-Methods"] = "GET, PUT, POST, DELETE, OPTIONS"
    cherrypy.response.headers["Access-Control-Allow-Credentials"] = "true"

def start_service():
	dispatcher = cherrypy.dispatch.RoutesDispatcher()
	
	# set routes
	dispatcher.connect('reset', '/reset/', controller=MovieController, action = 'RESET', conditions=dict(method=['PUT']))
	dispatcher.connect('movies_get', '/movies/:key', controller=MovieController, action = 'GET_MOVIE', conditions=dict(method=['GET']))
	dispatcher.connect('movies_get', '/movies/', controller=MovieController, action = 'GET_MOVIE_INDEX', conditions=dict(method=['GET']))
	dispatcher.connect('movies_put', '/movies/:key', controller=MovieController, action = 'PUT_MOVIE', conditions=dict(method=['PUT']))
	dispatcher.connect('movies_post', '/movies/', controller=MovieController, action = 'POST_MOVIE', conditions=dict(method=['POST']))
	dispatcher.connect('movies_delete', '/movies/:key', controller=MovieController, action = 'DELETE_MOVIE', conditions=dict(method=['DELETE']))
	dispatcher.connect('movies_delete_all', '/movies/', controller=MovieController, action = 'DELETE_ALL_MOVIES', conditions=dict(method=['DELETE']))
	dispatcher.connect('users_get', '/users/:key', controller=MovieController, action = 'GET_USER', conditions=dict(method=['GET']))
	dispatcher.connect('users_get', '/users/', controller=MovieController, action = 'GET_USER_INDEX', conditions=dict(method=['GET']))
	dispatcher.connect('users_put', '/users/:key', controller=MovieController, action = 'PUT_USER', conditions=dict(method=['PUT']))
	dispatcher.connect('users_post', '/users/', controller=MovieController, action = 'POST_USER', conditions=dict(method=['POST']))
	dispatcher.connect('users_delete', '/users/:key', controller=MovieController, action = 'DELETE_USER', conditions=dict(method=['DELETE']))
	dispatcher.connect('users_delete_all', '/users/', controller=MovieController, action = 'DELETE_ALL_USERS', conditions=dict(method=['DELETE']))
	dispatcher.connect('ratings_get', '/ratings/:key', controller=MovieController, action = 'GET_RATING', conditions=dict(method=['GET']))
	dispatcher.connect('recommendations_get', '/recommendations/:key', controller=MovieController, action = 'GET_RECOMMENDATION', conditions=dict(method=['GET']))
	dispatcher.connect('recommendations_put', '/recommendations/:key', controller=MovieController, action = 'PUT_RECOMMENDATION', conditions=dict(method=['PUT']))
	dispatcher.connect('recommendations_delete_all', '/recommendations/', controller=MovieController, action = 'DELETE_ALL_RECOMMENDATIONS', conditions=dict(method=['DELETE']))
	
	dispatcher.connect('options', '/options/', controller=OptionsController, action = 'OPTIONS', conditions=dict(method=['OPTIONS']))
	dispatcher.connect('options', '/recommendations/:key', controller=OptionsController, action = 'OPTIONS', conditions=dict(method=['OPTIONS']))

	conf = {
        'global': {
            'server.socket_host': 'student02.cse.nd.edu',
            'server.socket_port': 40042,
            },
        '/': {
            'request.dispatch': dispatcher,
            'tools.CORS.on': True,
            }
    }
	
	# update and start server
	cherrypy.config.update(conf)
	app = cherrypy.tree.mount(None, config=conf)
	cherrypy.quickstart(app)

if __name__ == '__main__':
	MovieController = MovieController()
	cherrypy.tools.CORS = cherrypy.Tool('before_handler', CORS)
	start_service()
