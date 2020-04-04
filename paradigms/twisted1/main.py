# Nathan Vahrenberg
# CSE30332 Programming Paradigms
# Twisted 1
# 18 April 2016

from twisted.internet import reactor
from twisted.internet.defer import Deferred
from twisted.internet.protocol import Protocol
from twisted.web.client import Agent, readBody
from twisted.web.http_headers import Headers

if __name__ == '__main__':

	SITE_URL = "http://student02.cse.nd.edu:40001"
	MOVIE_URL = "/movies/32"
	REQUEST_URL = SITE_URL + MOVIE_URL

	"""
	The agent/reactor will be set up to handle the server response. The request is what will be configured
	to send to the server.
	"""
	agent = Agent(reactor)
	request = agent.request(
		'GET',
		REQUEST_URL,
		Headers({'User-Agent': ['Twisted Daily 1']}),
		None)

	"""
	cbBody receives the body data from the response from cbRequest, and simply outputs it to the terminal
	before returning. No formatting is performed.
	"""
	def cbBody(body):
		print "received data:"
		print body
		print "\n\n"


	"""
	cbRequest is called when a response is received from the server. It prints out some metadata both
	provided by this program, and some header information received from the server response. Once it 
	has looped through all of the header information, it sends the response body to be handled by cbBody
	"""
	def cbRequest(response):
		print "connection made to " + SITE_URL + " for resource " + MOVIE_URL + "\n"
		print "received data:", response.version, response.code, response.phrase
		header_dict = response.headers.getAllRawHeaders()
		for header in header_dict:
			print header[0], ":", header[1][0]
		print "\n\n"
		d = readBody(response)
		d.addCallback(cbBody)
		return d
	request.addCallback(cbRequest)


	"""
	cbShutdown is called when the connection is closed. Right now all it does is notify
	the user that the connection has been closed, then closes the reactor.
	"""
	def cbShutdown(ignored):
		print "connection lost, exiting..."
		reactor.stop()
	request.addBoth(cbShutdown)

	reactor.run()