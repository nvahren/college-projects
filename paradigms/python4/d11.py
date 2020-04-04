# Nathan Vahrenberg
# Python Daily 4

from employee.employee import Employee, EmployeeA, EmployeeAB, EmployeeC
import csv

def giveEveryoneARaise(l):

	for employee in l:
		employee.giveRaise()

	return l

def giveDeptARaise(l, dept):

	for employee in l:
		if employee.dept == dept:
			employee.giveRaise()

	return l

def getHighestSalary(l):
	max_salary = 0
	highest_paid

	for employee in l:
		if employee.salary > max_salary:
			highest_paid = employee
			max_salary = employee.salary

	return highest_paid

def getAverageSalary(l):
	running_total = 0
	count = 0

	for employee in l:
		running_total += employee.salary
		count += 1

	return (running_total / count)

def getMedianSalary(l):
	salary_list = list()

	for employee in l:
		salary_list.append(employee.salary)

	salary_list.sort()

	if len(salary_list)%2 == 0:
		return (salary_list[len(salary_list)/2] + salary_list[len(salary_list)/2-1]) / 2
	else:
		return salary_list[(len(salary_list)-1)/2]

def getOnePercent(l):
	l.sort(key=lambda x: x.salary, reverse=True)
	count = 0

	top_one_percent = list()
	for employee in l:
		if count < len(l)*0.01:
			top_one_percent.append(employee)
			count += 1
		else:
			break

	return top_one_percent


if __name__ == '__main__':

	# initialize variables
	employee_list = list()
	role_dict = {}

	# open role file
	with open('roleclass.csv') as csvfile:
		role_reader = csv.DictReader(csvfile, fieldnames = ['role','class'])
		
		# for each row of the file
		for row in role_reader:
		
			# if it isn't an empty row
			if len(row) > 0:
				
				# add key and value to dict
				role_dict[row['role']] = row['class']

	# open employee file
	with open('chisalaries.csv') as csvfile:
		reader = csv.DictReader(csvfile)
		
		# for each row of the file
		for row in reader:
		
			# if it isn't an empty row
			if len(row['Name']) > 0:
			
				# convert the salary string to a float
				row['Employee Annual Salary'] = float(row['Employee Annual Salary'].replace("$",""))
				
				# add the employee object to the list
				if role_dict[row['Position Title']] == "A":
					employee_list.append( EmployeeA(row['Name'],row['Position Title'],row['Department'],row['Employee Annual Salary']) )
				elif role_dict[row['Position Title']] == "AB":
					employee_list.append( EmployeeAB(row['Name'],row['Position Title'],row['Department'],row['Employee Annual Salary']) )
				elif role_dict[row['Position Title']] == "C":
					employee_list.append( EmployeeC(row['Name'],row['Position Title'],row['Department'],row['Employee Annual Salary']) )
				else:
					print "Unrecognized role", role_dict[row['Position Title']]


	print ""

	# compute percentages per role
	total_A = 0
	total_AB = 0
	total_C = 0
	for employee in employee_list:
		if employee.__class__.__name__ == "EmployeeA":
			total_A += employee.salary
		elif employee.__class__.__name__ == "EmployeeAB":
			total_AB += employee.salary
		elif employee.__class__.__name__ == "EmployeeC":
			total_C += employee.salary
		else:
			print "Unrecognized class name", employee.__class__.__name__

	total = total_A + total_AB + total_C

	print "Percent A:  %.2f%%" % float(100*total_A / total)
	print "Percent AB: %.2f%%" % float(100*total_AB / total)
	print "Percent C:  %.2f%%" % float(100*total_C / total)

	print ""

	# give everyone 5 raises
	print "Giving everyone 5 raises\n"
	for i in range(0, 4):
		employee_list = giveEveryoneARaise(employee_list)
	

	# compute percentages per role
	total_A = 0
	total_AB = 0
	total_C = 0
	for employee in employee_list:
		if employee.__class__.__name__ == "EmployeeA":
			total_A += employee.salary
		elif employee.__class__.__name__ == "EmployeeAB":
			total_AB += employee.salary
		elif employee.__class__.__name__ == "EmployeeC":
			total_C += employee.salary
		else:
			print "Unrecognized class name", employee.__class__.__name__

	total = total_A + total_AB + total_C

	print "Percent A:  %.2f%%" % float(100*total_A / total)
	print "Percent AB: %.2f%%" % float(100*total_AB / total)
	print "Percent C:  %.2f%%" % float(100*total_C / total)

	print ""
	
	# print median and average
	print "Median Salary: $%.2f" % getMedianSalary(employee_list)
	print "Average Salary: $%.2f" % getAverageSalary(employee_list)

	print ""
