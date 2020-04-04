# Nathan Vahrenberg
# CSE30332 Programming Paradigms
# Twisted 2
# 20 April 2016

from twisted.internet import reactor, protocol
from twisted.internet.defer import Deferred
from twisted.internet.protocol import Protocol
from twisted.web.client import Agent, readBody
from twisted.web.http_headers import Headers
from twisted.internet.endpoints import TCP4ServerEndpoint

if __name__ == '__main__':

	PORT = 40042

	class PrintServer(protocol.Protocol):
		def connectionMade(self):
			print "connection received from", self.transport.getPeer()

		def dataReceived(self, data):
			print "Data received:\n", data
			self.transport.loseConnection()

		def connectionLost(self, reason):
			if reactor.running:
				print "connection lost from", self.transport.getPeer()
				reactor.stop()

	factory = protocol.ServerFactory()
	factory.protocol = PrintServer
	endpoint = TCP4ServerEndpoint(reactor, 40042)
	endpoint.listen(factory)
	reactor.run()