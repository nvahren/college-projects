# Nathan Vahrenberg
# CSE30332 Programming Paradigms
# CherryPy Primer
# 4 March 2016

import json
import cherrypy

class DictionaryController(object):
	def __init__(self):
		self.myd = dict()
		
	# GET /dictionary/:key
	def GET(self, key):
		key = str(key)
		output = {}
		try:
			value = self.myd[key]
			output['result'] = 'success'
			output['key'] = key
			output['value'] = str(value)
		except:
			output['result'] = 'error'
			output['message'] = 'key not found'
		return json.dumps(output, encoding='latin-1')
		
	# GET /dictionary/
	def GET_INDEX(self):
		output = {'result':'success'}
		entries = []
		for key in self.myd:
			temp = {'key':key}
			temp['value'] = self.myd[key]
			entries.append(temp)
		output['entries'] = entries
		return json.dumps(output, encoding='latin-1')
			
	# PUT /dictionary/:key
	def PUT(self, key):
		key = str(key)
		request = cherrypy.request.body.read()
		request = json.loads(request)
		value = str(request['value'])
		self.myd[key] = value
		output = {'result':'success'}
		return json.dumps(output, encoding='latin-1')
		
	# DELETE /dictionary/:key	
	def DELETE(self, key):
		key = str(key)
		try:
			self.myd.pop(key, None)
			output = {'result':'success'}
		except:
			output['result'] = 'error'
			output['message'] = 'key not found'
		return json.dumps(output, encoding='latin-1')
			
	# DELETE /dictionary/
	def DELETE_ALL(self):
		self.myd.clear()
		output = {'result':'success'}
		return json.dumps(output, encoding='latin-1')
					
	# POST /dictionary/	
	def POST(self):
		request = cherrypy.request.body.read()
		request = json.loads(request)
		self.myd[request['key']] = request['value']
		output = {'result':'success'}
		return json.dumps(output, encoding='latin-1')
