
# test_d8.py: A tester for the Python Daily 8 function

# this reads the function definitions in d8.py
# but does not invoke any main functionality

import d8

file_name = 'upcsampledata.csv'

# open a file with some lines of text in it.
f = file(file_name,'r')

# slurp all of the lines of text into a list
lines = f.readlines()

# close the file
f.close()

n_lines = len(lines)

# how many lines did we get?
print 'Read ',n_lines,' lines from the file ',file_name

# how many words in the first line?
print 'There are ',d8.string_word_count(lines[0]),' words in the first line.'

# how many words in the "middle" of the file?
print 'There are ',d8.string_word_count(lines[n_lines/2]),' words in the middle line.'

# how many words are in the last line of the file?
print 'There are ',d8.string_word_count(lines[-1]),' words in the last line.'

# what is the AVERAGE number of words per line?
# calculate this by applying the function to each line in the file and
# gathering up the results in a list
nums = []
for l in lines:
	nums = nums + [ d8.string_word_count(l) ]

print 'calculated ',len(nums),' word counts (should be ',n_lines,')'

min_length = min(10,n_lines)

print ('Word counts for the first %i lines: ') % (min_length), ', '.join('%i' % num for num in nums[:min_length])

# OK, now add up all the lengths. This is a reduce operation

sum_of_lengths = sum(nums)

avg_of_lengths = 1.0*sum_of_lengths/n_lines

print ('Average length is %f') % (avg_of_lengths)
