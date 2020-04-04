# Nathan Vahrenberg
# CSE30332 Programming Paradigms
# Twisted Primer
# 29 April 2016

import os
import sys

from twisted.internet import reactor, protocol
from twisted.internet.defer import Deferred
from twisted.internet.protocol import Protocol
from twisted.internet.endpoints import TCP4ClientEndpoint
from twisted.internet.defer import DeferredQueue

# Info for home.py
HOME_URL = 'localhost'
COMMAND_PORT = 40042
DATA_PORT = 41042

# Info for forwarded connection
FORWARD_URL = 'student00.cse.nd.edu'
FORWARD_PORT = 22

# Queue for all data moving from home.py to the forwarded service
forwardQueue = DeferredQueue()

# Queue for all data moving from the service to home.py
reverseQueue = DeferredQueue()

# Queue used to add a disconnect callback
disconnectQueue = DeferredQueue()

# Set to True for verbose output
DEBUG = False

"""
CommandClient connects to home.py first and waits for home.py's signal to open more connections
"""
class CommandClient(Protocol):
	def connectionMade(self):
		if DEBUG:
			print "command: connection made"

	def dataReceived(self, data):
		if DEBUG:
			print "command: data received"
		reactor.connectTCP(HOME_URL, DATA_PORT, dataFactory)
		reactor.connectTCP(FORWARD_URL, FORWARD_PORT, forwardFactory)
    
    # Notify other protocols to disconnect then restart
	def connectionLost(self, reason):
		if DEBUG:
			print "command: connection lost"
		disconnectQueue.put("dc")
		disconnectQueue.put("dc")
		reactor.stop()

"""
DataClient receives data from the data connection and forwards data from the Forward connection
"""
class DataClient(Protocol):
	# Send data and queue another callback when finished
	def sendAndQueue(self, data):
		if DEBUG:
			print "data: forwarding data"
		self.transport.write(data)
		reverseQueue.get().addCallback(self.sendAndQueue)

	# Lose connection if command connection signals a disconnect
	def disconnect(self, reason):
		self.transport.loseConnection()

	def connectionMade(self):
		if DEBUG:
			print "data: connection made"
		reverseQueue.get().addCallback(self.sendAndQueue)
		disconnectQueue.get().addCallback(self.disconnect)

	def dataReceived(self, data):
		if DEBUG:
			print "data: data received"
		forwardQueue.put(data)

	def connectionLost(self, reason):
		if DEBUG:
			print "data: connection lost"

"""
ForwardClient is responsible for handling any data from the data connection to be sent on to the ssh connection
"""
class ForwardClient(Protocol):
	# Send data and queue another callback when finished
	def sendAndQueue(self, data):
		if DEBUG:
			print "forward: forwarding data"
		self.transport.write(data)
		forwardQueue.get().addCallback(self.sendAndQueue)

	# Lose connection if command connection signals a disconnect
	def disconnect(self, reason):
		self.transport.loseConnection()

	# Add disconnect to queue to end forward connection if data connection is lost
	def connectionMade(self):
		if DEBUG:
			print "forward: connection made"
		forwardQueue.get().addCallback(self.sendAndQueue)
		disconnectQueue.get().addCallback(self.disconnect)

	def dataReceived(self, data):
		if DEBUG:
			print "forward: data received"
		reverseQueue.put(data)
    
	def connectionLost(self, reason):
		if DEBUG:
			print "forward: connection lost"

# establish command connection to home
commandFactory = protocol.ClientFactory()
commandFactory.protocol = CommandClient
reactor.connectTCP(HOME_URL, COMMAND_PORT, commandFactory)

#prepare data connection but wait to connect
dataFactory = protocol.ClientFactory()
dataFactory.protocol = DataClient

#prepare forward connection but wait to connect
forwardFactory = protocol.ClientFactory()
forwardFactory.protocol = ForwardClient

reactor.run()

os.execl(sys.executable, sys.executable, *sys.argv)