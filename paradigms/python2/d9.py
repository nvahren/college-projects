# Nathan Vahrenberg
# Python Daily 2

import csv

if __name__ == '__main__':

	# initialize variables
	reader = list()
	sum_of_salaries = 0
	count_of_salaries = 0
	department_list = list()
	
	# open file
	with open('chisalaries.csv') as csvfile:
		reader = csv.DictReader(csvfile)
		
		# for each row of the file
		for row in reader:
		
			# if it isn't an empty row
			if len(row['Name']) > 0:
			
				# convert the salary string to a float
				row['Employee Annual Salary'] = float(row['Employee Annual Salary'].replace("$",""))
				
				# add the salary to the running sum
				sum_of_salaries += row['Employee Annual Salary']
				
				# add 1 to the count (not totally necessary but avoids empty row being counted)
				count_of_salaries += 1
				
				# add the department to the list
				department_list.append(row['Department'])
				
	# convert department list to set to remove duplicates			
	department_set = set(department_list)
			
	# blank line
	print ""
			
	# print payroll info
	print "Total payroll:       $%14.2f" % sum_of_salaries
	print "Number of employees:  %14d" % count_of_salaries
	print "Average yearly pay:  $%14.2f" % round((sum_of_salaries/count_of_salaries),2)
	
	# blank line
	print ""
	
	# print department info
	print "Number of city departments: %d" % len(department_set)
	print "Names of city departments:",
	for department in department_set:
		print "\"%s\"," % department,
	
	# blank lines
	print ""
	print ""
			
		
