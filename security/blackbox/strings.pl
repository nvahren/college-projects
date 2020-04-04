#!/usr/bin/perl

# Nathan Vahrenberg

# password-cracking program using Unix 'strings' function plus
# regex matching to scan the binary for possible passwords and
# test them against the binary

# usage: from the root directory of this project:
# $ ./src/strings.pl

use strict;
use warnings;

# run 'strings' and output to file
system("strings ./data/blackbox > ./output.txt");

# open file for reading
my $file = './output.txt';
open my $words, $file or die "Could not open $file: $!";

# intentionally fail so the program knows what the failure string is
my $denied = `./data/blackbox -p password`;

# for each line (word) in the file
while( my $word = <$words>)  {
    #print $word;
    
    # if the word is purely alphabetical
    if($word =~ /^[a-zA-Z]+$/){
    	
    	# test the password
    	my $output = `./data/blackbox -p ${word}`;
    	
   		#print $output;
   		
   		# if the output of blackbox is the same as the known failure
    	if ($output eq $denied){
    		#print "failed\n";
    		
    	# if it is different we probably found the password
    	}else{
    		print "\n\npassword: ";
    		print $word;
    		print "\n\n";
    		exit 0;
    	}
    	
    # if the word does not match the regex
    }else{
    	#print "skipping attempt ${word}\n"
    }
}

# cleaning up
close $words;
