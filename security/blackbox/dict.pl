#!/usr/bin/perl

# Nathan Vahrenberg

# password-cracking program using the Unix dictionary file located
# at /usr/share/dict/words to attempt all dictionary words (using a
# regex to exclude words containing certain characters)

# usage: from the root directory of this project:
# $ ./src/dict.pl

use strict;
use warnings;

# open file for reading
my $file = '/usr/share/dict/words';
open my $words, $file or die "Could not open $file: $!";

# intentionally fail so the program knows what the failure string is
my $denied = `./data/blackbox -p password`;

# for each word in the file
while( my $word = <$words>)  {
    #print $word;
    
    # if word is purely alphabetical
    if($word =~ /^[a-zA-Z]+$/){
    
    	# test the password
    	my $output = `./data/blackbox -p ${word}`;
    	
   		#print $output;
   		
   		# if the output of the blackbox is the same as the known failure
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

#cleaning up
close $words;
