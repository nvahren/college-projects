# Nathan Vahrenberg
# Python Primer
# 24 February 2016

class _movie_database:

	def __init__(self):
		self.movies = {}
		self.users = {}
		self.ratings = {}

	def load_movies(self, movie_file):
		with open(movie_file) as f:
			for line in f:
				key,movie,genre = line.split("::")
				self.movies[int(key)] = {'name' : movie, 'genres' : genre.strip()}

	def get_movie(self, mid):
		if mid in self.movies:
			title = self.movies[mid]['name']
			genre = self.movies[mid]['genres']
			return [title, genre]
		else:
			return None

	def get_movies(self):
		return self.movies

	def set_movie(self, mid, movie):
		self.movies[mid] = {'name' : movie[0], 'genres' : movie[1]}

	def delete_movie(self, mid):
		del self.movies[mid]

	def load_users(self, users_file):
		with open(users_file) as f:
			for line in f:
				key,gender,age,occupationcode,zipcode = line.split("::")
				self.users[int(key)] = {'gender' : gender, 'age' : age, 'occupationcode' : occupationcode, 'zipcode' : zipcode.strip()}	

	def get_user(self, uid):
		if uid in self.users:
			gender = self.users[uid]['gender']
			age = int(self.users[uid]['age'])
			occupationcode = int(self.users[uid]['occupationcode'])
			zipcode = self.users[uid]['zipcode']
			return [gender,age,occupationcode,zipcode]
		else:
			return None

	def set_user(self, uid, user):
		self.users[uid] = {'gender' : user[0], 'age' : user[1], 'occupationcode' : user[2], 'zipcode' : user[3]}

	def delete_user(self, uid):
		del self.users[uid]

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