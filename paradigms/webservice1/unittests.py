from _webservice_primer import _webservice_primer
import unittest

class TestWebServicePrimer(unittest.TestCase):

	#@classmethod
	#def setUpClass(self):
	MID = 43 # CHANGE TO YOUR MID
	MNAME = 'Restoration (1995)' # CHANGE TO YOUR MOVIE NAME
	API_KEY = '3rEMq572cB' # CHANGE TO YOUR API KEY
	ws = _webservice_primer(API_KEY)

	def reset_movie(self):
		# needed because we cannot promise an execution order
		self.ws.reset_movie(self.MID)

	def test_get_movie(self):
		self.reset_movie()
		movie = self.ws.get_movie(self.MID)
		self.assertEquals(movie['title'], self.MNAME)

	def test_set_movie_title(self):
		self.reset_movie()
		movie = self.ws.get_movie(self.MID)
		movie['title'] = 'Something Else'
		self.ws.set_movie_title(self.MID, movie['title'])
		movie = self.ws.get_movie(self.MID)
		self.assertEquals(movie['title'], 'Something Else')

	def test_delete_movie(self):
		self.reset_movie()
		self.ws.delete_movie(self.MID)
		movie = self.ws.get_movie(self.MID)
		self.assertEquals(movie['result'], 'error')

if __name__ == "__main__":
	unittest.main()

