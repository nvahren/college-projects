# Nathan Vahrenberg
# CSE 30332 Programming Paradigms
# PyQt Assignment
# 2 March 2016

from PyQt4.QtCore import *
from PyQt4.QtGui  import *

import sys
sys.path.append('/afs/nd.edu/user37/cmc/Public/paradigms/python/local/lib/python2.6/site-packages/requests-2.0.0-py2.6.egg')
import requests
import json
		
# class to display an error dialog
class errorWidget(QWidget):
	def __init__(self, message):
		QWidget.__init__(self)
		
		self.setWindowTitle("Error")
		
		self.vLayout = QVBoxLayout(self)
		
		self.message = QLabel(self)
		self.message.setText(message)
		
		self.closeButton = QPushButton("Close")
		self.closeButton.clicked.connect(self.closeWindow)
		
		self.vLayout.addWidget(self.message)
		self.vLayout.addWidget(self.closeButton)
		
	def closeWindow(self):
		self.close()
		
# class to display a dialog showing user info
class viewUserWidget(QWidget):
	
	def __init__(self, uid):
		QWidget.__init__(self)
		
		self.setWindowTitle("User Profile")
		
		self.vLayout = QVBoxLayout(self)
		
		self.USER_URL = 'http://student02.cse.nd.edu:40001/users/'
		r = requests.get(self.USER_URL + str(uid))
		resp = json.loads(r.content)
		
		self.gender = QLabel(self)
		self.gender.setText("Gender: " + resp['gender'])
		self.zipcode = QLabel(self)
		self.zipcode.setText("Zipcode: " + str(resp['zipcode']))
		self.age = QLabel(self)
		self.age.setText("Age: " + str(resp['age']))
		
		self.closeButton = QPushButton("Close")
		self.closeButton.clicked.connect(self.buttonClicked)
		
		self.vLayout.addWidget(self.gender)
		self.vLayout.addWidget(self.zipcode)
		self.vLayout.addWidget(self.age)
		self.vLayout.addWidget(self.closeButton)
		
	def buttonClicked(self):
		self.close()
	
# class to show a text box, allowing user to change uid
class changeUserWidget(QWidget):

	def __init__(self, parentWindow):
		QWidget.__init__(self)
		self.parentWindow = parentWindow
		self.setWindowTitle("Change User")
		
		self.vLayout = QVBoxLayout(self)
		self.buttonLayout = QHBoxLayout(self)
		
		self.textEdit = QTextEdit()
		
		self.okButton = QPushButton("Ok")
		self.okButton.clicked.connect(self.buttonClicked)
		self.cancelButton = QPushButton("Cancel")
		self.cancelButton.clicked.connect(self.closeWindow)
		
		self.buttonLayout.addWidget(self.okButton)
		self.buttonLayout.addWidget(self.cancelButton)
		
		self.vLayout.addWidget(self.textEdit)
		self.vLayout.addLayout(self.buttonLayout)
		
	def buttonClicked(self):
		# check if input is integer, show error message if not
		if str(self.textEdit.toPlainText()).isdigit():
			self.parentWindow.setUid(int(self.textEdit.toPlainText()))
			self.close()
		else:
			self.window = errorWidget("Please enter an integer")
			self.window.setGeometry(QRect(100, 100, 200, 100))
			self.window.show()
	
	def closeWindow(self):
		self.close()
		
# class for main window
class MoviesQT(QMainWindow):
	def __init__(self):
		super(MoviesQT, self).__init__()
		self.setWindowTitle("Movie Recommender")
		
		self.central = MoviesCentral(parent = self)
		self.setCentralWidget(self.central)		
		
# class for main window widget functionality
class MoviesCentral(QWidget):
	def __init__(self, parent=None):
		super(MoviesCentral, self).__init__(parent)
		
		# program parameters
		self.API_KEY = '3rEMq572cB'
		self.uid = 5
		self.SITE_URL = 'http://student02.cse.nd.edu:40001'
		self.IMG_DIR = '/afs/nd.edu/user37/cmc/Public/cse332_sp16/cherrypy/data/images/'
		self.RECOMMENDATIONS_URL = self.SITE_URL + '/recommendations/'
		self.MOVIES_URL = self.SITE_URL + '/movies/'
		self.RATINGS_URL = self.SITE_URL + '/ratings/'
		
		# layout
		self.hLayout = QHBoxLayout(self)
		self.buttonLayout = QVBoxLayout(self)
		self.movieLayout = QVBoxLayout(self)
		
		self.upButton = QPushButton("Up")
		self.downButton = QPushButton("Down")
		self.upButton.clicked.connect(self.buttonClicked)
		self.downButton.clicked.connect(self.buttonClicked)
		
		self.pic = QLabel(self)
		self.title = QLabel(self)
		self.genre = QLabel(self)
		self.rating = QLabel(self)
		
		self.hLayout.addLayout(self.buttonLayout)
		self.hLayout.addLayout(self.movieLayout)
		
		self.movieLayout.addWidget(self.pic)
		self.movieLayout.addWidget(self.title)
		self.movieLayout.addWidget(self.genre)
		self.movieLayout.addWidget(self.rating)
		
		self.buttonLayout.addWidget(self.upButton)
		self.buttonLayout.addWidget(self.downButton)
		
		self.loadRecommendation()
		
		# menu bar
		closeAction = QAction("&Close", self)
		closeAction.setShortcut("Ctrl+Q")
		closeAction.setStatusTip('Leave The App')
		closeAction.triggered.connect(self.closeApplication)
		
		viewUserAction = QAction("&View User", self)
		viewUserAction.triggered.connect(self.viewUser)
		changeUserAction = QAction("&Change User", self)
		changeUserAction.triggered.connect(self.changeUser)

		self.statusBar = QStatusBar(self)

		self.menuBar = QMenuBar(self)
		fileMenu = self.menuBar.addMenu('&File')
		fileMenu.addAction(closeAction)
		userMenu = self.menuBar.addMenu('&User')
		userMenu.addAction(viewUserAction)
		userMenu.addAction(changeUserAction)
		
	# GET from /recommendations/
	def loadRecommendation(self):
		r = requests.get(self.RECOMMENDATIONS_URL + str(self.uid))
		resp = json.loads(r.content)
		mid = resp['movie_id']
		self.mid = mid
		
		r = requests.get(self.MOVIES_URL + str(mid))
		movie_resp = json.loads(r.content)
		title = movie_resp['title']
		genre = movie_resp['genres']
		r = requests.get(self.RATINGS_URL + str(mid))
		rating_resp = json.loads(r.content)
		rating = rating_resp['rating']
		
		r = requests.get(self.MOVIES_URL + str(mid))
		resp = json.loads(r.content)
		img = resp['img']
		
		self.title.setText(title)
		self.genre.setText(genre)
		self.rating.setText("Rating: " + str(round(rating,2)))
		
		self.pixmap = QPixmap(self.IMG_DIR + str(img))
		self.pixmap = self.pixmap.scaledToHeight(300)
		self.pic.setPixmap(self.pixmap)
	
	# PUT to /recommendations/
	def sendRating(self, rating):
		data = {}
		data['rating'] = str(rating)
		data['apikey'] = self.API_KEY
		data['movie_id'] = str(self.mid)
		r = requests.put(self.RECOMMENDATIONS_URL + str(self.uid), data = json.dumps(data))
	
	# handle button press (for both buttons)
	def buttonClicked(self):
		sender = self.sender()
		if sender.text() == "Up":
			self.loadRecommendation()
			self.sendRating(5)
		elif sender.text() == "Down":
			self.loadRecommendation()
			self.sendRating(1)
		else:
			print "Error: Command not recognized"
		
	# helper for changeUser
	def setUid(self, uid):
		self.uid = uid
		self.loadRecommendation()
			
	# called by "View User" in menu bar
	def viewUser(self):
		self.window = viewUserWidget(self.uid)
		self.window.setGeometry(QRect(100, 100, 200, 100))
		self.window.show()
		
	# called by "Change User" in menu bar
	def changeUser(self):
		self.window = changeUserWidget(self)
		self.window.setGeometry(QRect(100, 100, 200, 100))
		self.window.show()
		
	# called by "Close" in menu bar
	def closeApplication(self):
		sys.exit()
		
# main function to launch gui window
if __name__ == "__main__":
	app = QApplication(sys.argv)
	gui = MoviesQT()
	gui.setGeometry(QRect(100, 100, 500, 250))
	gui.show()
	sys.exit(app.exec_())
