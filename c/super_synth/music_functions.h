//music_functions.h
//Header file for piano.c and music_functions.c.
//Author:  Christopher Ray		//Date:  06 November 2013

double note_select(char c);

double change_octave(char c);

int change_tempo(char c);

void create_waveform(double frequency, int tempo, int volume, FILE * f);

void create_synth_waveform(double frequency, int tempo, int instrument, int volume, FILE * f);

void average_waveform(short chordform[5][WAVFILE_SAMPLES_PER_SECOND], short fingers, int NUM_SAMPLES, FILE * f);

void create_chord_waveform(int c, double frequency, int tempo, int volume, int instrument, short fingers, short chordform[5][WAVFILE_SAMPLES_PER_SECOND], FILE * f); 

void input_reader(int c, double * fp, double * op, int * tp, int * ip, int volume, FILE * f);

void chord_reader(int * cp, double * fp, double * op, int * tp, int * ip, char * name, int volume, FILE * f, FILE * e);

void choose_instrument(int * cp, char name[5], int * ip, FILE * e);
