# Nathan Vahrenberg
# CSE30332 Programming Paradigms
# AJAX
# 8 April 2016

import json
import cherrypy

from _movie_database import _movie_database

class MovieController(object):

	mdb = _movie_database()

	def __init__(self):
		self.mdb.__init__()
		self.mdb.load_movies('ml-1m/movies.dat')
		self.mdb.load_users('ml-1m/users.dat')
		self.mdb.load_ratings('ml-1m/ratings.dat')
		self.mdb.load_posters('images.dat')
		
	
	def RESET(self):
		output = {'result':'success'}
		# note that you need authentication code here, too
		self.mdb.__init__()
		self.mdb.load_movies('ml-1m/movies.dat')
		self.mdb.load_users('ml-1m/users.dat')
		self.mdb.load_ratings('ml-1m/ratings.dat')
		self.mdb.load_posters('images.dat')
		return json.dumps(output, encoding='latin-1')
		
	# GET /movies/:key
	def GET_MOVIE(self, key):
		key = str(key)
		output = {}
		try:
			movie = self.mdb.get_movie(key)
			output['result'] = 'success'
			output['id'] = key
			output['title'] = movie[0]
			output['genres'] = movie[1]
			output['img'] = self.mdb.get_poster(key)
		except:
			output['result'] = 'error'
			output['message'] = 'movie not found'
		return json.dumps(output, encoding='latin-1')
		
	# GET /movies/
	def GET_MOVIE_INDEX(self):
		output = {'result':'success'}
		keys = self.mdb.get_movies()
		movies = []
		for key in keys:
			data = self.mdb.get_movie(key)
			movie = {}
			movie['title'] = data[0]
			movie['genres'] = data[1]
			movie['id'] = key
			movie['img'] = self.mdb.get_poster(key)
			movie['result'] = 'success'
			movies.append(movie)
		output['movies'] = movies
		return json.dumps(output, encoding='latin-1')

	# GET /users/:key
	def GET_USER(self, key):
		key = str(key)
		output = {}
		try:
			user = self.mdb.get_user(key)
			output['gender'] = user[0]
			output['age'] = user[1]
			output['occupation'] = user[2]
			output['zipcode'] = user[3]
			output['id'] = key
			output['result'] = 'success'
		except:
			output['result'] = 'error'
			output['message'] = 'user not found'
		return json.dumps(output, encoding='latin-1')
		
	# GET /users/
	def GET_USER_INDEX(self):
		output = {'result':'success'}
		keys = self.mdb.get_users()
		users = []
		for key in keys:
			data = self.mdb.get_user(key)
			user = {}
			user['gender'] = data[0]
			user['age'] = data[1]
			user['occupation'] = data[2]
			user['zipcode'] = data[3]
			user['id'] = key
			user['result'] = 'success'
			users.append(user)
		output['users'] = users
		return json.dumps(output, encoding='latin-1')

	# GET /ratings/:key
	def GET_RATING(self, key):
		key = str(key)
		output = {}
		try:
			rating = self.mdb.get_rating(key)
			output['rating'] = rating
			output['movie_id'] = int(key)
			output['result'] = 'success'
		except:
			output['result'] = 'error'
			output['message'] = 'rating not found'
		return json.dumps(output, encoding='latin-1')

	# GET /recommendations/:key
	def GET_RECOMMENDATION(self, key):
		key = str(key)
		output = {}
		mid = self.mdb.get_highest_rated_unvoted_movie(key)
		output['movie_id'] = mid
		output['result'] = 'success'
		return json.dumps(output, encoding='latin-1')

	# PUT /recommendations/:key
	def PUT_RECOMMENDATION(self, key):
		key = str(key)
		request = cherrypy.request.body.read()
		request = json.loads(request)
		self.mdb.add_vote(key, str(request['movie_id']), str(request['rating']))
		output = {'result':'success'}
		return json.dumps(output, encoding='latin-1')
			
	# PUT /movies/:key
	def PUT_MOVIE(self, key):
		key = str(key)
		request = cherrypy.request.body.read()
		request = json.loads(request)
		self.mdb.set_movie(key, [str(request['title']),str(request['genres'])])
		output = {'result':'success'}
		return json.dumps(output, encoding='latin-1')

	# PUT /users/:key
	def PUT_USER(self, key):
		key = str(key)
		request = cherrypy.request.body.read()
		request = json.loads(request)
		self.mdb.set_user(key, [str(request['gender']),int(request['age']),int(request['occupation']),str(request['zipcode'])])
		output = {'result':'success'}
		return json.dumps(output, encoding='latin-1')
		
	# DELETE /movies/:key	
	def DELETE_MOVIE(self, key):
		output = dict()
		key = str(key)
		try:
			self.mdb.delete_movie(key)
			output = {'result':'success'}
		except:
			output['result'] = 'error'
			output['message'] = 'movie not found'
		return json.dumps(output, encoding='latin-1')

		# DELETE /users/:key	
	def DELETE_USER(self, key):
		output = dict()
		key = str(key)
		try:
			self.mdb.delete_user(key)
			output = {'result':'success'}
		except:
			output['result'] = 'error'
			output['message'] = 'movie not found'
		return json.dumps(output, encoding='latin-1')
			
	# DELETE /movies/
	def DELETE_ALL_MOVIES(self):
		self.mdb.delete_all_movies()
		output = {'result':'success'}
		return json.dumps(output, encoding='latin-1')

	# DELETE /users/
	def DELETE_ALL_USERS(self):
		self.mdb.delete_all_users()
		output = {'result':'success'}
		return json.dumps(output, encoding='latin-1')
					
	# POST /movies/	
	def POST_MOVIE(self):
		request = cherrypy.request.body.read()
		request = json.loads(request)
		key = self.mdb.add_movie([request['title'],request['genres']])
		output = {'result':'success'}
		output['id'] = key
		return json.dumps(output, encoding='latin-1')

	# POST /users/	
	def POST_USER(self):
		request = cherrypy.request.body.read()
		request = json.loads(request)
		key = self.mdb.add_user([request['gender'],request['age'],request['occupation'],request['zipcode']])
		output = {'result':'success'}
		output['id'] = key
		return json.dumps(output, encoding='latin-1')

	# DELETE /recommendations/
	def DELETE_ALL_RECOMMENDATIONS(self):
		self.mdb.delete_all_ratings()
		output = {'result':'success'}
		return json.dumps(output, encoding='latin-1')
