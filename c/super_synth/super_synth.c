//synth.c
//This program is an exact duplicate of piano.c, albeit with a more interesting waveform.
//Author:  Christopher Ray		//Date:  10 November 2013

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "wavfile.h"
#include "music_functions.h"

int main(int argc, char * argv[])
{
	//declaring variables	
	double frequency = 440.00; //initial frequency	
	double * fp = &frequency; //pointer to frequency
	double octave = 1; //initial octave
	double * op = &octave; //pointer to octave
	int tempo = WAVFILE_SAMPLES_PER_SECOND; //initial tempo
	int * tp = &tempo; //pointer to tempo
	int volume = 16000;  //volume
	int c; //user input
	int * cp = &c; //pointer to user input
	char name[5]; //name of instrument
	int instrument = 4; //initial instrument (piano)
	int * ip = &instrument; //pointer to instrument

	FILE * e = fopen(argv[1], "r"); //opening file to be read from
	if(e == NULL)
	{
		perror("Error opening write file.");
		return 0;
	}

	FILE * f = wavfile_open(argv[2]); //opening and naming the wav file to be written
	if(f == NULL)
	{
		perror("Error opening write file.");
		return 0;
	}

	printf("\033[2J\033[H"); //clearing the screen because I like having a blank slate to start
	
	c = fgetc(e); //reading user input from file
	while(c != EOF) //the program will read from the .music file until it reaches the end of the file
	{	
		switch(c)
		{
			case '(': // '(' indicates the start of a chord
			chord_reader(cp, fp, op, tp, ip, name, volume, f, e);
			break;	

			case ')': // '(' indicates the end of a chord
			break;

			case'[': // '[' indicates inputting a string for determining which instrument to switch to
			choose_instrument(cp, name, ip, e);
			break;

			case']': // ']' indicates ending of string input
			break;		
						
			case 'X': //ending the program and closing both files
			case 'x':
			wavfile_close(f);
			fclose(e);
			return 0;
			break;

			default: //interpretting all other user input
			input_reader(c, fp, op, tp, ip, volume, f);
			break;
		}
		c = fgetc(e); 
	}
	return 0;
}
