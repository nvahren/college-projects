# Nathan Vahrenberg
# CSE30332 Programming Paradigms
# Twisted 3
# 22 April 2016

from twisted.internet import reactor, protocol
from twisted.internet.defer import Deferred
from twisted.internet.protocol import Protocol
from twisted.web.http_headers import Headers
from twisted.internet.endpoints import TCP4ServerEndpoint
from twisted.internet.defer import DeferredQueue

if __name__ == '__main__':

	LISTEN_PORT = 40042

	DATABASE_URL = "student02.cse.nd.edu"
	DATABASE_PORT = 40001

	queue = DeferredQueue()

	global sharedData


	"""
	FromClientServer is responsible for handling any communication between this program and the client program.
	It passes its data to ToDatabaseClient via a global variable sharedData, and is responsible for kicking
	off the connection to the database.
	"""
	class FromClientServer(protocol.Protocol):

		"""
		forwardDataToDB first takes the data sent from the client and saves it as the global variable sharedData,
		then instructs the reactor to begin establishing a connection to the database. While that is happening,
		this function also queues the forwardDataToClient function to prepare to send the response from the DB
		to the client.
		"""
		def forwardDataToDB(self, data):
			#print "prepare to forward data to DB:", data

			global sharedData 
			sharedData = data

			reactor.connectTCP(DATABASE_URL, DATABASE_PORT, ToDatabaseFactory())

			queue.get().addCallback(self.forwardDataToClient)
			queue.get().addCallback(self.forwardDataToClient)


		"""
		forwardDataToClient is called when the DeferredQueue acquires the data from the database, and is responsible
		for handling the sending of that data back to the client.
		"""
		def forwardDataToClient(self, data):
			#print "forward data to client:", data
			self.transport.write(data)

		"""
		connectionMade only outputs a debug message that a connection from the client has been received.
		"""
		def connectionMade(self):
			print "connection received from", self.transport.getPeer()

		"""
		dataReceived calls forwardDataToDB to handle any incoming requests from the client.
		"""
		def dataReceived(self, data):
			#print "Data received:\n", data
			self.forwardDataToDB(data)

		"""
		connectionLost notifies the user that the connection to the client has ceased and that the reactor will be
		stopping.
		"""
		def connectionLost(self, reason):
			if reactor.running:
				print "connection lost from", self.transport.getPeer()
				reactor.stop()

	"""
	ToDatabaseClient is responsible for any communication between this program and the database, and is dormant
	until a client connects, at which point it will be called to establish a connection with the database.
	"""
	class ToDatabaseClient(protocol.Protocol):

		"""
		connectionMade waits for a connection from the database, and notifies the user that it has been established.
		Next, it obtains the string stored in the global sharedData and forwards it to the database.
		"""
		def connectionMade(self):
			print "database connection successful to", self.transport.getPeer()

			global sharedData
			#print "SENDING", sharedData
			self.transport.write(sharedData)
			

		"""
		dataReceived takes any data from the database and moves it to the DeferredQueue, where FromClientServer
		has set up methods waiting to handle it.
		"""
		def dataReceived(self, data):
			#print "response from database:", data
			queue.put(data)

	"""
	ToDatabaseFactory works as a wrapper for ToDatabaseClient and handles loss of connectivity.
	"""
	class ToDatabaseFactory(protocol.ClientFactory):
		protocol = ToDatabaseClient

		"""
		clientConnectionLost is called when the database connection ends and notifies the user that the reactor
		will be stopping.
		"""
		def clientConnectionLost(self, connector, reason):
			print "database connection lost"
			reactor.stop()


	clientFactory = protocol.ServerFactory()
	clientFactory.protocol = FromClientServer
	endpoint = TCP4ServerEndpoint(reactor, LISTEN_PORT)
	endpoint.listen(clientFactory)

	reactor.run()