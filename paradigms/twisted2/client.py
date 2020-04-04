# Nathan Vahrenberg
# CSE30332 Programming Paradigms
# Twisted 2
# 20 April 2016

from twisted.internet import reactor, protocol
from twisted.internet.defer import Deferred
from twisted.internet.protocol import Protocol
from twisted.web.client import Agent, readBody
from twisted.web.http_headers import Headers
from twisted.internet.endpoints import TCP4ClientEndpoint

if __name__ == '__main__':

	SITE_URL = "http://127.0.0.1:40042"
	MOVIE_URL = "/movies/32"
	REQUEST_URL = SITE_URL + MOVIE_URL
	PORT = 40042

	class PrintClient(Protocol):
    
		def connectionMade(self):
			print "Connection made to", SITE_URL
			agent = Agent(reactor)
			request = agent.request(
				'GET',
				REQUEST_URL,
				Headers({'User-Agent': ['Twisted Daily 2']}),
				None)

			def cbResponse(ignored):
				print 'Response received'
			request.addCallback(cbResponse)

			def cbShutdown(ignored):
				self.transport.loseConnection()
			request.addBoth(cbShutdown)
    
    	def connectionLost(self, reason):
        	print "connection to", SITE_URL, "lost"

	class PrintFactory(protocol.ClientFactory):
		protocol = PrintClient

		def clientConnectionLost(self, connector, reason):
			reactor.stop()

	factory = PrintFactory()
	reactor.connectTCP('localhost', 40042, factory)
	reactor.run()
	print "connection to", SITE_URL, "lost"