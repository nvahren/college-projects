# Nathan Vahrenberg
# CSE30332 Programming Paradigms
# CherryPy Homework
# 18 March 2016

class _movie_database:

	def __init__(self):
		self.movies = {}
		self.users = {}
		self.ratings = {}
		self.posters = {}
		self.votes = []

	def load_movies(self, movie_file):
		with open(movie_file) as f:
			for line in f:
				key,movie,genre = line.split("::")
				self.movies[int(key)] = {'name' : movie, 'genres' : genre.strip()}

	def load_posters(self, posters_file):
		with open(posters_file) as f:
			for line in f:
				line = line.rstrip()
				components = line.split("::")
				mid = int(components[0])
				mimg = components[2]
				self.posters[mid] = mimg

	def get_poster(self, mid):
		if int(mid) in self.posters.keys():
			return self.posters[int(mid)]
		return '/default.jpg'


	def get_movie(self, mid):
		mid = int(mid)
		if mid in self.movies:
			title = self.movies[mid]['name']
			genre = self.movies[mid]['genres']
			return [title, genre]
		else:
			return None

	def get_movies(self):
		return self.movies

	def set_movie(self, mid, movie):
		mid = int(mid)
		self.movies[mid] = {'name' : movie[0], 'genres' : movie[1]}

	def add_movie(self, movie):
		key = 0
		for mid in self.movies:
			if mid > key:
				key = mid
		key += 1
		self.set_movie(key, movie)
		return key

	def delete_movie(self, mid):
		mid = int(mid)
		del self.movies[mid]

	def delete_all_movies(self):
		self.movies.clear()

	def load_users(self, users_file):
		with open(users_file) as f:
			for line in f:
				key,gender,age,occupationcode,zipcode = line.split("::")
				self.users[int(key)] = {'gender' : gender, 'age' : age, 'occupationcode' : occupationcode, 'zipcode' : zipcode.strip()}	

	def get_user(self, uid):
		uid = int(uid)
		if uid in self.users:
			gender = self.users[uid]['gender']
			age = int(self.users[uid]['age'])
			occupationcode = int(self.users[uid]['occupationcode'])
			zipcode = self.users[uid]['zipcode']
			return [gender,age,occupationcode,zipcode]
		else:
			return None

	def get_users(self):
		return self.users

	def set_user(self, uid, user):
		uid = int(uid)
		self.users[uid] = {'gender' : user[0], 'age' : user[1], 'occupationcode' : user[2], 'zipcode' : user[3]}

	def add_user(self, user):
		key = 0
		for mid in self.users:
			if mid > key:
				key = mid
		key += 1
		self.set_user(key, user)
		return key

	def delete_user(self, uid):
		uid = int(uid)
		del self.users[uid]

	def delete_all_users(self):
		self.users.clear()

	def load_ratings(self, ratings_file):
		with open(ratings_file) as f:
			for line in f:
				uid,mid,rating,timestamp = line.split("::")
				mid = int(mid)
				self.ratings[mid] = {}
		with open(ratings_file) as f:
			for line in f:
				uid,mid,rating,timestamp = line.split("::")
				mid = int(mid)
				uid = int(uid)
				rating = int(rating)
				self.ratings[mid][uid] = rating

	def get_rating(self, mid):
		mid = int(mid)
		count = 0
		rating_sum = 0.0
		if mid in self.ratings.keys():
			for key in self.ratings[mid].keys():
				rating_sum += self.ratings[mid][key]
				count += 1
			return float(rating_sum)/count
		else:
			return 0

	def get_highest_rated_movie(self):
		highest = 1
		for key in self.movies.keys():
			if self.get_rating(key) > self.get_rating(highest):
				highest = key
		return highest

	def add_vote(self, uid, mid, vote):
		uid = int(uid)
		mid = int(mid)
		vote = int(vote)
		self.votes.append({'uid':uid,'mid':mid,'vote':vote})
		self.ratings[mid][uid] = vote

	def user_has_voted_on_movie(self, uid, mid):
		uid = int(uid)
		mid = int(mid)
		try:
			if self.ratings[mid][uid] > 0:
				return True
			return False
		except:
			return False

	def get_highest_rated_unvoted_movie(self, uid):
		highest = 1
		for key in self.movies.keys():
			if self.get_rating(key) > self.get_rating(highest):
				if not self.user_has_voted_on_movie(uid, key):
					highest = key
		return highest

	def set_user_movie_rating(self, uid, mid, rating):
		if not mid in self.ratings.keys():
			self.ratings[mid] = {}
		self.ratings[mid][uid] = rating

	def get_user_movie_rating(self, uid, mid):
		if mid in self.ratings.keys():
			if uid in self.ratings[mid].keys():
				return self.ratings[mid][uid]
		return 0

	def delete_all_ratings(self):
		self.ratings.clear()
