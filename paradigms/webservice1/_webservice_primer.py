import sys
sys.path.append('/afs/nd.edu/user37/cmc/Public/paradigms/python/local/lib/python2.6/site-packages/requests-2.0.0-py2.6.egg')
import requests
import json

class _webservice_primer:
	def __init__(self, apikey):
		self.API_KEY = apikey
		self.SITE_URL = 'http://student02.cse.nd.edu:40001'
		self.MOVIES_URL = self.SITE_URL + '/movies/'
		self.RESET_URL = self.SITE_URL + '/reset/'

	def get_movie(self, mid):
		mid = str(mid)
		r = requests.get(self.MOVIES_URL + mid)
		resp = json.loads(r.content)
		return resp

	def set_movie_title(self, mid, title):
		movie = self.get_movie(mid)
		movie['title'] = title
		movie['apikey'] = self.API_KEY
		r = requests.put(self.MOVIES_URL + str(mid), data = json.dumps(movie))

	def reset_movie(self, mid):
		mydata = {}
		mydata['apikey'] = self.API_KEY
		r = requests.put(self.RESET_URL + str(mid), data = json.dumps(mydata))
		resp = json.loads(r.content)
		return resp
		
	def delete_movie(self, mid):
		mydata = {}
		mydata['apikey'] = self.API_KEY
		r = requests.delete(self.MOVIES_URL + str(mid), data = json.dumps(mydata))

if __name__ == "__main__":
	MID = 43
	API_KEY = '3rEMq572cB'
	ws = _webservice_primer(API_KEY)

	movie = ws.get_movie(MID)
	if movie['result'] == 'success':
		print "Title:\t%s" % movie['title']
	else:
		print "Error:\t%s" % movie['message']

