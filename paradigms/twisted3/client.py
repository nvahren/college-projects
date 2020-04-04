# Nathan Vahrenberg
# CSE30332 Programming Paradigms
# Twisted 3
# 22 April 2016

from twisted.internet import reactor, protocol
from twisted.internet.defer import Deferred
from twisted.internet.protocol import Protocol
from twisted.web.http_headers import Headers
from twisted.internet.endpoints import TCP4ClientEndpoint

if __name__ == '__main__':

	SITE_URL = "http://127.0.0.1:40042"
	MOVIE_URL = "/movies/32"
	REQUEST_URL = SITE_URL + MOVIE_URL
	PORT = 40042


	"""
	PrintClient issues the GET request to the server (or proxy) and waits for the response(s).
	"""
	class PrintClient(Protocol):
    
		"""
		connectionMade sends the GET request once the TCP connection has been established.
    	"""
		def connectionMade(self):
			print "Connection made to", SITE_URL
			self.transport.write("GET /movies/32 HTTP/1.0\r\n\r\n")

		"""
		dataReceived outputs any response received to the terminal.
		"""
		def dataReceived(self, data):
			print "Response received:", data
    
    	"""
    	connectionLost notifies the user if the connection is lost
    	"""
    	def connectionLost(self, reason):
        	print "connection to", SITE_URL, "lost"


	"""
    PrintFactory is the wrapper for PrintClient and stops the reactor if the connection is lost.
    """
	class PrintFactory(protocol.ClientFactory):
		protocol = PrintClient

		"""
		clientConnectionLost notifies the user and stops the reactor if the server/proxy connection is lost.
		"""
		def clientConnectionLost(self, connector, reason):
			print "connection to", SITE_URL, "lost"
			reactor.stop()

	factory = PrintFactory()
	reactor.connectTCP('localhost', 40042, factory)
	reactor.run()