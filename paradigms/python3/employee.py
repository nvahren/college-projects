# Nathan Vahrenberg
# Python Daily 3

class Employee:

	next_employee_number = 0

	def __init__(self,name,title,dept,salary):
		employee_number = Employee.next_employee_number
		Employee.next_employee_number += 1
		self.name = name
		self.title = title
		self.dept = dept
		self.salary = salary

	def __str__(self):
		return "[Employee name: %s, %s, %s, $%.2f]" % (self.name, self.title, self.dept, self.salary)

	def getName(self):
		return self.name

	def setName(self, name):
		self.name = name

	def getTitle(self):
		return self.title

	def setTitle(self, title):
		self.title = title

	def getDept(self):
		return self.dept

	def setDept(self, dept):
		self.dept = dept

	def getSalary(self):
		return self.salary

	def setSalary(self, salary):
		self.salary = salary

	def giveRaise(self, percentage):
		self.salary = self.salary * (1.00+(percentage*0.01))
