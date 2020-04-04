# Nathan Vahrenberg
# Python Daily 3

from employee import Employee
import csv

def giveEveryoneARaise(l, percentage):

	for employee in l:
		employee.giveRaise(percentage)

	return l

def giveDeptARaise(l, dept, percentage):

	for employee in l:
		if employee.dept == dept:
			employee.giveRaise(percentage)

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
	
	# open file
	with open('chisalaries.csv') as csvfile:
		reader = csv.DictReader(csvfile)
		
		# for each row of the file
		for row in reader:
		
			# if it isn't an empty row
			if len(row['Name']) > 0:
			
				# convert the salary string to a float
				row['Employee Annual Salary'] = float(row['Employee Annual Salary'].replace("$",""))
				
				# add the employee object to the list
				employee_list.append( Employee(row['Name'],row['Position Title'],row['Department'],row['Employee Annual Salary']) )

	print ""

	# print median and average
	print "Median Salary: $%.2f" % getMedianSalary(employee_list)
	print "Average Salary: $%.2f" % getAverageSalary(employee_list)

	# 5% raise for all
	print "\nGiving everyone a 5% raise...\n"
	employee_list = giveEveryoneARaise(employee_list, 5)

	# print median and average
	print "Median Salary: $%.2f" % getMedianSalary(employee_list)
	print "Average Salary: $%.2f" % getAverageSalary(employee_list)

	# 6% raise for dept "FIRE"
	print "\nGiving department \"FIRE\" a 6% raise...\n"
	employee_list = giveDeptARaise(employee_list, "FIRE", 6)

	# print median and average
	print "Median Salary: $%.2f" % getMedianSalary(employee_list)
	print "Average Salary: $%.2f" % getAverageSalary(employee_list)

	#print median and average only for top 1% of employees
	print "\nFor the top 1%...\n"

	print "Median Salary: $%.2f" % getMedianSalary(getOnePercent(employee_list))
	print "Average Salary: $%.2f" % getAverageSalary(getOnePercent(employee_list))	

	print ""




