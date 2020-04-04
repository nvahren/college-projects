# Python daily 8: string length counting
# Nathan Vahrenberg

def string_word_count(s):
	"""Return the number of words in the string parameter s."""
	return len(s.split())

# the following idiom runs a test of the method, but only if the
# python script is run. If it is imported, the code below will not
# be executed.

if __name__ == '__main__':
	test_string = 'Notre Dame, our Mother\nTender, Strong and True'
	correct_wc = 8
	wc = string_word_count(test_string)
	print 'Test string appears below, in between === lines: '
	print '==='
	print test_string
	print '==='
	print 'Correct word count: ',correct_wc
	print 'Computed word count: ',wc
