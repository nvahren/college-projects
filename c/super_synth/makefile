EXEC = super_synth

$(EXEC): super_synth.c music_functions.c
	gcc super_synth.c music_functions.c wavfile.c -o $(EXEC) -lm
	
clean:
	rm $(EXEC) *.wav
