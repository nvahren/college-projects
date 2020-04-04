# Nathan Vahrenberg
# CSE30332 Programming Paradigms
# Twisted Primer
# 29 April 2016

import os
import sys

from twisted.internet import reactor, protocol
from twisted.internet.defer import Deferred
from twisted.internet.protocol import Protocol
from twisted.internet.endpoints import TCP4ServerEndpoint
from twisted.internet.defer import DeferredQueue


# Ports to open
COMMAND_PORT = 40042
DATA_PORT = 41042
CLIENT_PORT = 42042


# Queue for all data moving from the client service to work.py
forwardQueue = DeferredQueue()

# Queue for all data moving from work.py to the client
reverseQueue = DeferredQueue()

# Queue used to add a disconnect callback
disconnectQueue = DeferredQueue()


# Set to True for verbose output
DEBUG = False

"""
CommandServer waits for a connection from work.py then notifies work.py to open connections when a client
connects
"""
class commandServer(protocol.Protocol):

	# Lose connection if the client disconnects
	def disconnect(self, reason):
		self.transport.loseConnection()

	# Queue notification for work.py then queue disconnect
	def connectionMade(self):
		if DEBUG:
			print "command: connection made"
		forwardQueue.get().addCallback(self.transport.write)
		disconnectQueue.get().addCallback(self.disconnect)

	def dataReceived(self, data):
		if DEBUG:
			print "command: data received"

	def connectionLost(self, reason):
		if DEBUG:
			print "command: connection lost"

"""
clientServer opens a port and waits for a client to connect
"""
class clientServer(protocol.Protocol):

	# Send data then re-queue self once finished, indicating ready to send again
	def sendAndQueue(self, data):
		if DEBUG:
			print "client: forwarding data"
		self.transport.write(data)
		reverseQueue.get().addCallback(self.sendAndQueue)

	# Notify work.py (if online) to open data and forward connections
	def connectionMade(self):
		if DEBUG:
			print "client: connection made"
		forwardQueue.put("command")
		reverseQueue.get().addCallback(self.sendAndQueue)

	def dataReceived(self, data):
		if DEBUG:
			print "client: data received"
		forwardQueue.put(data)

	# Close connections and restart if client disconnects
	def connectionLost(self, reason):
		if DEBUG:
			print "client: connection lost"
			disconnectQueue.put("dc")
			disconnectQueue.put("dc")
			reactor.stop()

"""
dataServer waits for the data connection from work.py, which will forward traffic from the client and
remote service both directions
"""
class dataServer(protocol.Protocol):

	# send data and re-queue self, indicating ready to send again
	def sendAndQueue(self, data):
		if DEBUG:
			print "data: forwarding data"
		self.transport.write(data)
		forwardQueue.get().addCallback(self.sendAndQueue)
		disconnectQueue.get().addCallback(self.disconnect)

	# Lose connection if client disconnects
	def disconnect(self, reason):
		self.transport.loseConnection()

	def connectionMade(self):
		if DEBUG:
			print "data: connection made"
		forwardQueue.get().addCallback(self.sendAndQueue)

	def dataReceived(self, data):
		if DEBUG:
			print "data: data received"
		reverseQueue.put(data)

	def connectionLost(self, reason):
		if DEBUG:
			print "data: connection lost"

# listen for command connection
commandFactory = protocol.ServerFactory()
commandFactory.protocol = commandServer
commandEndpoint = TCP4ServerEndpoint(reactor, COMMAND_PORT)
commandEndpoint.listen(commandFactory)

# listen for client connection
clientFactory = protocol.ServerFactory()
clientFactory.protocol = clientServer
clientEndpoint = TCP4ServerEndpoint(reactor, CLIENT_PORT)
clientEndpoint.listen(clientFactory)

# listen for data connection
dataFactory = protocol.ServerFactory()
dataFactory.protocol = dataServer
dataEndpoint = TCP4ServerEndpoint(reactor, DATA_PORT)
dataEndpoint.listen(dataFactory)

reactor.run()

os.execl(sys.executable, sys.executable, *sys.argv)