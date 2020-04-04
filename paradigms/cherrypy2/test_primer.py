# Nathan Vahrenberg
# CSE30332 Programming Paradigms
# CherryPy Primer
# 4 March 2016

# Changes made to this file:
#   Added 'sys.append...' to find 'requests' package
#   Changed SITE_URL to reflect IP address and port

import sys
sys.path.append('/afs/nd.edu/user37/cmc/Public/paradigms/python/local/lib/python2.6/site-packages/requests-2.0.0-py2.6.egg')

import unittest
import requests
import json

class TestCherrypyPrimer(unittest.TestCase):

	#@classmethod
	#def setUpClass(self):
	#SITE_URL = 'http://student02.cse.nd.edu:40042'
	SITE_URL = 'http://127.0.0.1:40042'
	DICT_URL = SITE_URL + '/dictionary/'

	def reset_data(self):
		r = requests.delete(self.DICT_URL)

	def is_json(self, resp):
		try:
			json.loads(resp)
			return True
		except ValueError:
			return False

	def test_dict_get(self):
		self.reset_data()
		key = 'a4'
		r = requests.get(self.DICT_URL + key)
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'error')

	def test_dict_put(self):
		self.reset_data()
		key = 'a4'

		m = {}
		m['value'] = '1995'
		r = requests.put(self.DICT_URL + key, data = json.dumps(m))
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'success')

		r = requests.get(self.DICT_URL + key)
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['value'], m['value'])

	def test_dict_delete(self):
		self.reset_data()
		key = 'a4'

		m = {}
		m['value'] = '1995'
		r = requests.put(self.DICT_URL + key, data = json.dumps(m))
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'success')

		r = requests.delete(self.DICT_URL + key)
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'success')

		r = requests.get(self.DICT_URL + key)
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'error')

	def test_dict_index_get(self):
		self.reset_data()

		key = 'a4'
		m = {}
		m['value'] = '1995'
		r = requests.put(self.DICT_URL + key, data = json.dumps(m))
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'success')

		r = requests.get(self.DICT_URL)
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'success')

		entries = resp['entries']
		mkv = entries[0]
		self.assertEquals(mkv['key'], key)
		self.assertEquals(mkv['value'], m['value'])

	def test_dict_index_post(self):
		self.reset_data()

		m = {}
		m['key'] = 'a4'
		m['value'] = '1995'

		r = requests.post(self.DICT_URL, data = json.dumps(m))
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'success')

		r = requests.get(self.DICT_URL)
		self.assertTrue(self.is_json(r.content))
		resp = json.loads(r.content)
		self.assertEquals(resp['result'], 'success')

		entries = resp['entries']
		mkv = entries[0]
		self.assertEquals(mkv['key'], m['key'])
		self.assertEquals(mkv['value'], m['value'])

if __name__ == "__main__":
	unittest.main()

