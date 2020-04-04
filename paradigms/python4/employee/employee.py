# Nathan Vahrenberg
# Python Daily 3

class Employee:

	next_employee_number = 0

	default_salary_inflator = 1.04

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

	def giveRaise(self):
		self.salary = self.salary * default_salary_inflator

class EmployeeA(Employee):

	inflator_A = 1.02

	def giveRaise(self):
		self.salary = self.salary * self.default_salary_inflator * self.inflator_A

	def __str__(self):
		return "[EmployeeA name: %s, %s, %s, $%.2f]" % (self.name, self.title, self.dept, self.salary)

class EmployeeC(Employee):

	inflator_C = 1.01

	def giveRaise(self):
		self.salary = self.salary * self.default_salary_inflator * self.inflator_C

	def __str__(self):
		return "[EmployeeC name: %s, %s, %s, $%.2f]" % (self.name, self.title, self.dept, self.salary)

class EmployeeAB(EmployeeA):

	inflator_B = 1.08

	def giveRaise(self):
		self.salary = self.salary * self.default_salary_inflator * self.inflator_A * self.inflator_B

	def __str__(self):
		return "[EmployeeAB name: %s, %s, %s, $%.2f]" % (self.name, self.title, self.dept, self.salary)
