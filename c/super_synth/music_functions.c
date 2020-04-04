//music_functions.c
//File containing functions for use in piano.c.
//Author:  Christopher Ray		Date:  06 November 2013

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "wavfile.h"
#include "music_functions.h"

double note_select(char c) //function for adding a new note
{
	double frequency = 440.00; //initializing the frequency
	switch(c) //user will input a note and the switch statement will change the frequency to that of the selected note
	{
		case 'a':
		frequency = 415.30; 
		break;

		case 'A':
		frequency = 440.00; 
		break;

		case 'b':
		frequency = 466.16; 
		break;

		case 'B':
		frequency = 493.88; 
		break;

		case 'C':
		frequency = 523.25; 
		break;

		case 'd':
		frequency = 554.37; 
		break;

		case 'D':
		frequency = 587.33; 
		break;

		case 'e':
		frequency = 622.25; 
		break;

		case 'E':
		frequency = 659.26; 
		break;

		case 'F':
		frequency = 698.46; 
		break;

		case 'g':
		frequency = 739.99; 
		break;

		case 'G':
		frequency = 783.99; 
		break;

		case '.': //a musical rest
		frequency = 0;
		break;
		
		default: //any illegal inputs this function will result in a frequency of 440.00
		frequency = 440.00;
		break;
	}
	return frequency;
}

double change_octave(char c) //funnction for changing octaves
{
	switch(c) //user's input determines which constant is returned for use in the main function
	{
		case '+':
		return 2;
		break;

		case '-':
		return 0.5;
		break;
		
		default: //an illegal input will result in a 1 being returned (which has no effect in the main function)
		return 1;
		break;
	}	
}

int change_tempo(char c) //function for changing tempo
{
	int tempo = WAVFILE_SAMPLES_PER_SECOND / 2; //initializing tempo	
	switch(c) //user's input will determine which constant is returned for use in the main function
	{	
		case '1':
		tempo = WAVFILE_SAMPLES_PER_SECOND * 2; 
		break;
		
		case '2':
		tempo = WAVFILE_SAMPLES_PER_SECOND; 
		break;

		case '4':
		tempo = WAVFILE_SAMPLES_PER_SECOND / 2; 
		break;

		case '8':
		tempo = WAVFILE_SAMPLES_PER_SECOND / 4; 
		break;

		case '6':
		tempo = WAVFILE_SAMPLES_PER_SECOND / 8; 
		break;

		default: //an illegal input results in the original tempo being returned
		tempo = WAVFILE_SAMPLES_PER_SECOND / 2;
		break;
	}
	return tempo;
}

void create_waveform(double frequency, int tempo, int volume, FILE * f) //function for creating the waveform and writing the file in piano.c
{
	int NUM_SAMPLES = tempo;
	short waveform[NUM_SAMPLES];
	double t;
	int i;

	for(i = 0; i < NUM_SAMPLES; i++) //the array is filled as the for loop runs
	{
		t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
		waveform[i] = volume * sin(frequency * t * 2 * M_PI);
	}
	
	wavfile_write(f, waveform, NUM_SAMPLES); //the data is added to the file "music.wav"
	return;
}

void create_synth_waveform(double frequency, int tempo, int instrument, int volume, FILE * f) //function for creating single note waveforms in super_synth.c
{
	int NUM_SAMPLES = tempo;
	short waveform[NUM_SAMPLES];
	double t;
	int i;

	//the following variables are used to create the waveforms for the 5 instruments	
	double attackFadeIn;
	double releaseFadeOut;
	double FirstHarmonic;
	double FH;
	double SecondHarmonic;
	double SH;

	for(i = 0; i < NUM_SAMPLES; i++) //the array is filled as the for loop runs
	{
		t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
		switch(instrument) //the value of instrument determines which waveform will be generated
		{
			case 1: //creating a flute waveform
			attackFadeIn = 6400.0;
			releaseFadeOut = 2.0;
			FirstHarmonic = 2/3;
			FH = 2;
			SecondHarmonic = 1/3;
			SH = 4;
			
			if (i <= attackFadeIn)
			{
				waveform[i] = (short)((volume*i/attackFadeIn) * ((sin(frequency*t*2*M_PI)) + 
						            (FirstHarmonic*sin(FH*frequency*t*2*M_PI)) + 
						            (SecondHarmonic*sin(SH*frequency*t*2*M_PI))));
				if(waveform[i] > 32767)
				{
					waveform[i] = 32767;
				}
				else if(waveform[i] < -32768)
				{
					waveform[i] = -32768;
				}
			}
			else if ((volume-((i-attackFadeIn)/releaseFadeOut)) >= 0)
			{
				waveform[i] = (short)((volume-((i-attackFadeIn)/releaseFadeOut)) * ((sin(frequency*t*2*M_PI)) + 
						                                 (FirstHarmonic*sin(FH*frequency*t*2*M_PI)) + 
						                                 (SecondHarmonic*sin(SH*frequency*t*2*M_PI))));
				if(waveform[i] > 32767)
				{
					waveform[i] = 32767;
				}
				else if(waveform[i] < -32768)
				{
					waveform[i] = -32768;
				}
			}
			else
			{
				waveform[i] = 0;
			}
			break;

			case 2: //creating a trumpet waveform
			attackFadeIn = 16000.0; 
			releaseFadeOut = 8.0;
			FirstHarmonic = 2/3;
			FH = 3;
			SecondHarmonic = 1/3;
			SH = 5;

			if (i <= attackFadeIn)
			{
				waveform[i] = (short) (volume*i/attackFadeIn * 
				((t*frequency - floor(1/2 + t*frequency)) +
				FirstHarmonic*(t*frequency - floor(1/2 + t*FH*frequency)) +
				SecondHarmonic*(t*frequency - floor(1/2 + t*SH*frequency))));
		
				if(waveform[i] > 32767)
				{
					waveform[i] = 32767;
				}
				else if(waveform[i] < -32768)
				{
					waveform[i] = -32768;
				}
			}
			else if ((volume-((i-attackFadeIn)/releaseFadeOut)) >= 0)
			{
				waveform[i] = (short) ((volume-((i-attackFadeIn)/releaseFadeOut)) * 
				((t*frequency - floor(1/2 + t*frequency)) +
				FirstHarmonic*(t*frequency - floor(1/2 + t*FH*frequency)) +
				SecondHarmonic*(t*frequency - floor(1/2 + t*SH*frequency))));

				if(waveform[i] > 32767)
				{
					waveform[i] = 32767;
				}
				else if(waveform[i] < -32768)
				{
					waveform[i] = -32768;
				}
			}
			else
			{
				waveform[i] = 0;
			}
			break;

			case 3: //creating a clarinet waveform
			attackFadeIn = 6400.0;
			releaseFadeOut = 6.0;
			FirstHarmonic = 1;
			FH = 2;
			SecondHarmonic = 2/3;
			SH = 4;

			if (i <= attackFadeIn)
			{
				waveform[i] = (short) ((volume*i/attackFadeIn)/2 * ( ((sin(frequency*2*M_PI*t) > 0)? 1 : -1) + 
						            FirstHarmonic* ((sin(FH*frequency*2*M_PI*t) > 0)? 1 : -1) + 
						            SecondHarmonic* ((sin(SH*frequency*2*M_PI*t) > 0)? 1 : -1) ));

				if(waveform[i] > 32767)
				{
					waveform[i] = 32767;
				}
				else if(waveform[i] < -32768)
				{
					waveform[i] = -32768;
				}
			}
			else if ((volume-((i-attackFadeIn)/releaseFadeOut)) >= 0)
			{
				waveform[i] = (short) ((volume-((i-attackFadeIn)/releaseFadeOut))/2 * (((sin(frequency*2*M_PI*t) > 0)? 1 : -1) + 
						                                 FirstHarmonic*((sin(FH*frequency*2*M_PI*t) > 0)? 1 : -1) + 
						                                 SecondHarmonic*((sin(SH*frequency*2*M_PI*t) > 0)? 1 : -1)));

				if(waveform[i] > 32767)
				{
					waveform[i] = 32767;
				}
				else if(waveform[i] < -32768)
				{
					waveform[i] = -32768;
				}
			}
			else
			{
				waveform[i] = 0;
			}
			break;

			case 4: //creating a piano waveform
			attackFadeIn = 64.0;
			releaseFadeOut = 2.0;
			FirstHarmonic = 2/3;
			FH = 2;
			SecondHarmonic = 1/3;
			SH = 5;

			if (i <= attackFadeIn)
			{
				waveform[i] = (short) ((volume*i/attackFadeIn) * ((sin(2*M_PI*frequency*t)) + 
						            FirstHarmonic*(sin(2*M_PI*frequency*FH*t)) + 
						            SecondHarmonic*(sin(2*M_PI*frequency*SH*t))));

				if(waveform[i] > 32767)
				{
					waveform[i] = 32767;
				}
				else if(waveform[i] < -32768)
				{
					waveform[i] = -32768;
				}
			}
			else if ((volume-((i-attackFadeIn)/releaseFadeOut)) >= 0)
			{
				waveform[i] = (short) ((volume-((i-attackFadeIn)/releaseFadeOut)) * ((sin(2*M_PI*frequency*t)) + 
						                                 FirstHarmonic*(sin(2*M_PI*frequency*FH*t)) + 
						                                 SecondHarmonic*(sin(2*M_PI*frequency*SH*t))));

				if(waveform[i] > 32767)
				{
					waveform[i] = 32767;
				}
				else if(waveform[i] < -32768)
				{
					waveform[i] = -32768;
				}
			}
			else
			{
				waveform[i] = 0;
			}
			break;

			case 5: //creating a holophoner waveform
			attackFadeIn = 6400.0;
			releaseFadeOut = 2;
			FirstHarmonic = 3/4;
			FH = 2;
			SecondHarmonic = 1/2;
			SH = 3;

			if (i <= attackFadeIn)
			{
				waveform[i] = (short) ((volume*i/attackFadeIn) * ((4*frequency * (t - 1/(2*frequency) * floor(2*t*frequency+1/2)) * pow(-1,floor(2*t*frequency+1/2))) + 
						            FirstHarmonic*(4*frequency*FH * (t - 1/(2*frequency*FH) * floor(2*t*frequency*FH+1/2)) * pow(-1,floor(2*t*frequency*FH+1/2))) + 
						            SecondHarmonic*(4*frequency*SH * (t - 1/(2*frequency*SH) * floor(2*t*frequency*SH+1/2)) * pow(-1,floor(2*t*frequency*SH+1/2)))));

				if(waveform[i] > 32767)
				{
					waveform[i] = 32767;
				}
				else if(waveform[i] < -32768)
				{
					waveform[i] = -32768;
				}
			}
			else if ((volume-((i-attackFadeIn)/releaseFadeOut)) >= 0)
			{
				waveform[i] = (short) ((volume-((i-attackFadeIn)/releaseFadeOut)) * ((4*frequency * (t - 1/(2*frequency) * floor(2*t*frequency+1/2)) * pow(-1,floor(2*t*frequency+1/2))) + 
						            FirstHarmonic*(4*frequency*FH * (t - 1/(2*frequency*FH) * floor(2*t*frequency*FH+1/2)) * pow(-1,floor(2*t*frequency*FH+1/2))) + 
						            SecondHarmonic*(4*frequency*SH * (t - 1/(2*frequency*SH) * floor(2*t*frequency*SH+1/2)) * pow(-1,floor(2*t*frequency*SH+1/2)))));

				if(waveform[i] > 32767)
				{
					waveform[i] = 32767;
				}
				else if(waveform[i] < -32768)
				{
					waveform[i] = -32768;
				}
			}
			else
			{
				waveform[i] = 0;
			}
			break;
		}
	}
	
	wavfile_write(f, waveform, NUM_SAMPLES); //the data is added to the .wav file eing written
	return;
}

void average_waveform(short chordform[5][WAVFILE_SAMPLES_PER_SECOND], short fingers, int NUM_SAMPLES, FILE * f) //chord for averaging a chord waveform (to prevent overload)
{
	int i = 0;
	int j = 0;
	short sum = 0;
	short newform[NUM_SAMPLES];

	if(fingers == 5) //The user can enter only 5 notes per chord.  This statement is for a full five note chord.
	{
		for(i = 0; i < NUM_SAMPLES; i++) //It goes through each column of chordform and averages the values in the rows.
		{
			for(j = 0; j < fingers; j++)
			{
				sum += (chordform[j][i] / (10 * fingers));
			}
			newform[i] = sum / (fingers);
		}	
	}
	else //same mechanics as above, just for all other chord forms
	{	
		for(i = 0; i < NUM_SAMPLES; i++)
		{
			for(j = 0; j < fingers + 1; j++)
			{
				sum += (chordform[j][i] / (10 * (fingers + 1)));
			}
			newform[i] = sum / (fingers + 1);
		}
	}
	
	wavfile_write(f, newform, NUM_SAMPLES);	//writing the chord to the .wav file
	return;
}

void create_chord_waveform(int c, double frequency, int tempo, int volume, int instrument, short fingers, short chordform[5][WAVFILE_SAMPLES_PER_SECOND], FILE * f) //function for generating a chord waveform
{
	int NUM_SAMPLES = tempo;
	double t;
	int i;

	double attackFadeIn;
	double releaseFadeOut;
	double FirstHarmonic;
	double FH;
	double SecondHarmonic;
	double SH;

	if((c == ')') || (fingers == 5)) //this prevents chords consisting of more than five notes and also signals when the user has inidicated the end of a chord
	{
		average_waveform(chordform, fingers, NUM_SAMPLES, f);
	}
	else //this section uses the same mechanics of create_synth_waveform
	{
		for(i = 0; i < NUM_SAMPLES; i++) 
		{
			t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
			switch(instrument)
			{
				case 1:
				attackFadeIn = 6400.0;
				releaseFadeOut = 2.0;
				FirstHarmonic = 2/3;
				FH = 2;
				SecondHarmonic = 1/3;
				SH = 4;
			
				if (i <= attackFadeIn)
				{
					chordform[fingers][i] = (short) ((volume*i/attackFadeIn) * ((sin(frequency*t*2*M_PI)) + 
								    (FirstHarmonic*sin(FH*frequency*t*2*M_PI)) + 
								    (SecondHarmonic*sin(SH*frequency*t*2*M_PI))));
					if(chordform[fingers][i] > 32767)
					{
						chordform[fingers][i] = 32767;
					}
					else if(chordform[fingers][i] < -32768)
					{
						chordform[fingers][i] = -32768;
					}
				}
				else if ((volume-((i-attackFadeIn)/releaseFadeOut)) >= 0)
				{
					chordform[fingers][i] = (short) ((volume-((i-attackFadeIn)/releaseFadeOut)) * ((sin(frequency*t*2*M_PI)) + 
								                         (FirstHarmonic*sin(FH*frequency*t*2*M_PI)) + 
								                         (SecondHarmonic*sin(SH*frequency*t*2*M_PI))));
					if(chordform[fingers][i] > 32767)
					{
						chordform[fingers][i] = 32767;
					}
					else if(chordform[fingers][i] < -32768)
					{
						chordform[fingers][i] = -32768;
					}
				}
				else
				{
					chordform[fingers][i] = 0;
				}
				break;

				case 2:
				attackFadeIn = 16000.0; 
				releaseFadeOut = 8.0;
				FirstHarmonic = 2/3;
				FH = 3;
				SecondHarmonic = 1/3;
				SH = 5;

				if (i <= attackFadeIn)
				{
					chordform[fingers][i] = (short) (volume*i/attackFadeIn * 
					((t*frequency - floor(1/2 + t*frequency)) +
					FirstHarmonic*(t*frequency - floor(1/2 + t*FH*frequency)) +
					SecondHarmonic*(t*frequency - floor(1/2 + t*SH*frequency))));

					if(chordform[fingers][i] > 32767)
					{
						chordform[fingers][i] = 32767;
					}
					else if(chordform[fingers][i] < -32768)
					{
						chordform[fingers][i] = -32768;
					}
				}
				else if ((volume-((i-attackFadeIn)/releaseFadeOut)) >= 0)
				{
					chordform[fingers][i] = (short) ((volume-((i-attackFadeIn)/releaseFadeOut)) * 
					((t*frequency - floor(1/2 + t*frequency)) +
					FirstHarmonic*(t*frequency - floor(1/2 + t*FH*frequency)) +
					SecondHarmonic*(t*frequency - floor(1/2 + t*SH*frequency))));

					if(chordform[fingers][i] > 32767)
					{
						chordform[fingers][i] = 32767;
					}
					else if(chordform[fingers][i] < -32768)
					{
						chordform[fingers][i] = -32768;
					}
				}
				else
				{
					chordform[fingers][i] = 0;
				}
				break;

				case 3:
				attackFadeIn = 6400.0;
				releaseFadeOut = 6.0;
				FirstHarmonic = 1;
				FH = 2;
				SecondHarmonic = 2/3;
				SH = 4;

				if (i <= attackFadeIn)
				{
					chordform[fingers][i] = (short) ((volume*i/attackFadeIn)/2 * ( ((sin(frequency*2*M_PI*t) > 0)? 1 : -1) + 
								    FirstHarmonic* ((sin(FH*frequency*2*M_PI*t) > 0)? 1 : -1) + 
								    SecondHarmonic* ((sin(SH*frequency*2*M_PI*t) > 0)? 1 : -1) ));
					if(chordform[fingers][i] > 32767)
					{
						chordform[fingers][i] = 32767;
					}
					else if(chordform[fingers][i] < -32768)
					{
						chordform[fingers][i] = -32768;
					}
				}
				else if ((volume-((i-attackFadeIn)/releaseFadeOut)) >= 0)
				{
					chordform[fingers][i] = (short) ((volume-((i-attackFadeIn)/releaseFadeOut))/2 * (((sin(frequency*2*M_PI*t) > 0)? 1 : -1) + 
								                         FirstHarmonic*((sin(FH*frequency*2*M_PI*t) > 0)? 1 : -1) + 
								                         SecondHarmonic*((sin(SH*frequency*2*M_PI*t) > 0)? 1 : -1)));
					if(chordform[fingers][i] > 32767)
					{
						chordform[fingers][i] = 32767;
					}
					else if(chordform[fingers][i] < -32768)
					{
						chordform[fingers][i] = -32768;
					}
				}
				else
				{
					chordform[fingers][i] = 0;
				}
				break;

				case 4:
				attackFadeIn = 64.0;
				releaseFadeOut = 2.0;
				FirstHarmonic = 2/3;
				FH = 2;
				SecondHarmonic = 1/3;
				SH = 5;

				if (i <= attackFadeIn)
				{
					chordform[fingers][i] = (short) ((volume*i/attackFadeIn) * ((sin(2*M_PI*frequency*t)) + 
								    FirstHarmonic*(sin(2*M_PI*frequency*FH*t)) + 
								    SecondHarmonic*(sin(2*M_PI*frequency*SH*t))));
					if(chordform[fingers][i] > 32767)
					{
						chordform[fingers][i] = 32767;
					}
					else if(chordform[fingers][i] < -32768)
					{
						chordform[fingers][i] = -32768;
					}
				}
				else if ((volume-((i-attackFadeIn)/releaseFadeOut)) >= 0)
				{
					chordform[fingers][i] = (short) ((volume-((i-attackFadeIn)/releaseFadeOut)) * ((sin(2*M_PI*frequency*t)) + 
								                         FirstHarmonic*(sin(2*M_PI*frequency*FH*t)) + 
								                         SecondHarmonic*(sin(2*M_PI*frequency*SH*t))));
					if(chordform[fingers][i] > 32767)
					{
						chordform[fingers][i] = 32767;
					}
					else if(chordform[fingers][i] < -32768)
					{
						chordform[fingers][i] = -32768;
					}
				}
				else
				{
					chordform[fingers][i] = 0;
				}
				break;

				case 5:
				attackFadeIn = 6400.0;
				releaseFadeOut = 2;
				FirstHarmonic = 3/4;
				FH = 2;
				SecondHarmonic = 1/2;
				SH = 3;

				if (i <= attackFadeIn)
				{
					chordform[fingers][i] = (short) ((volume*i/attackFadeIn) * ((4*frequency * (t - 1/(2*frequency) * floor(2*t*frequency+1/2)) * pow(-1,floor(2*t*frequency+1/2))) + 
								    FirstHarmonic*(4*frequency*FH * (t - 1/(2*frequency*FH) * floor(2*t*frequency*FH+1/2)) * pow(-1,floor(2*t*frequency*FH+1/2))) + 
								    SecondHarmonic*(4*frequency*SH * (t - 1/(2*frequency*SH) * floor(2*t*frequency*SH+1/2)) * pow(-1,floor(2*t*frequency*SH+1/2)))));
					if(chordform[fingers][i] > 32767)
					{
						chordform[fingers][i] = 32767;
					}
					else if(chordform[fingers][i] < -32768)
					{
						chordform[fingers][i] = -32768;
					}
				}
				else if ((volume-((i-attackFadeIn)/releaseFadeOut)) >= 0)
				{
					chordform[fingers][i] = (short) ((volume-((i-attackFadeIn)/releaseFadeOut)) * ((4*frequency * (t - 1/(2*frequency) * floor(2*t*frequency+1/2)) * pow(-1,floor(2*t*frequency+1/2))) + 
								    FirstHarmonic*(4*frequency*FH * (t - 1/(2*frequency*FH) * floor(2*t*frequency*FH+1/2)) * pow(-1,floor(2*t*frequency*FH+1/2))) + 
								    SecondHarmonic*(4*frequency*SH * (t - 1/(2*frequency*SH) * floor(2*t*frequency*SH+1/2)) * pow(-1,floor(2*t*frequency*SH+1/2)))));
					if(chordform[fingers][i] > 32767)
					{
						chordform[fingers][i] = 32767;
					}
					else if(chordform[fingers][i] < -32768)
					{
						chordform[fingers][i] = -32768;
					}
				}
				else
				{
					chordform[fingers][i] = 0;
				}
				break;
			}
		}
	}
	return;
}

void input_reader(int c, double * fp, double * op, int * tp, int * ip, int volume, FILE * f) //function for reading user input
{
	switch(c)
	{
		case '+': //changing the octave
		case '-':
		*op *= change_octave(c);
		break;

		case '1': //changing tempo
		case '2':
		case '4':
		case '8':
		case '6':
		*tp = change_tempo(c);
		break;

		case 'a': //adding a note
		case 'A':
		case 'b':
		case 'B':
		case 'C':
		case 'd':
		case 'D':
		case 'e':
		case 'E':
		case 'F':
		case 'g':
		case 'G':
		case '.':
		*fp = *op * note_select(c);
		create_synth_waveform(*fp, *tp, *ip, volume, f);
		break;
			
		case ' ': //ignoring blank spaces and newlines in input
		case '\n':
		break;

		default: //catching any invalid inputs
		printf("Invalid input (%c) skipped.\n", c);
		break;
	}	
	return;
}

void chord_reader(int * cp, double * fp, double * op, int * tp, int * ip, char * name, int volume, FILE * f, FILE * e) //function for reading chord inputs
{
	short fingers = 0; //indicates the number of notes in the chord
	short chordform[5][WAVFILE_SAMPLES_PER_SECOND]; //array for storing the waveforms for each note in the chord
	
	*cp = fgetc(e);	//reading user input
	while(fingers < 5)
	{
		switch(*cp)
		{
			case '+': //changing the octave
			case '-':
			*op *= change_octave(*cp);
			break;

			case 'a': //adding a note
			case 'A':
			case 'b':
			case 'B':
			case 'C':
			case 'd':
			case 'D':
			case 'e':
			case 'E':
			case 'F':
			case 'g':
			case 'G':
			case '.':
			*fp = *op * note_select(*cp);
			if(*ip == 2){*ip = 3;} //the trumpet causes an error when generating chords, so this line changes the instrument to the clarinet, which has a similar sound
			create_chord_waveform(*cp, *fp, *tp, volume, *ip, fingers, chordform, f); 
			fingers++;
			break;
			
			case ' ': //ignoring blank spaces and newlines in input
			case '\n':
			break;

			case'[': //indicates the use inputting a string for changing the instrument
			choose_instrument(cp, name, ip, e);
			break;

			case']': //indicates the end of string input
			break;

			case')': //indicates the end of a chord
			create_chord_waveform(*cp, *fp, *tp, volume, *ip, fingers, chordform, f);
			return;
			break;

			default: //catching any invalid inputs
			printf("Invalid input (%c) skipped.\n", *cp);
			break;
		}
		*cp = fgetc(e);
	}
	create_chord_waveform(*cp, *fp, *tp, volume, *ip, fingers, chordform, f);	
	return;
}

void choose_instrument(int * cp, char name[5], int * ip, FILE * e) //function for changing instruments
{
	int i = 0;	
	for(i = 0; i < 4; i++) //reading the string input
	{
		*cp = fgetc(e);
		name[i] = toupper(*cp);
	}
	name[i] = '\0';
	
	if(strcmp(name, "FLUT") == 0) //flute = 1
	{
		*ip = 1;
	}
	else if(strcmp(name, "TRUM") == 0) //trumpet = 2
	{
		*ip = 2;
	}
	else if(strcmp(name, "CLAR") == 0) //clarinet = 3
	{
		*ip = 3;
	}
	else if(strcmp(name, "PIAN") == 0) //piano = 4
	{
		*ip = 4;
	}
	else if(strcmp(name, "HOLO") == 0) //holophoner = 5
	{
		*ip = 5;
	}
	else
	{
		printf("Instrument '%s' not recognized.  Piano selected.\n", name); //invalid inputs result in the default piano being selected		
		*ip = 4;
	}	
	return;
}

