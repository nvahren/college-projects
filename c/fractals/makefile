EXEC = fractals

$(EXEC): fractals.c gfx.c gfx.h
	gcc fractals.c gfx.c -o $(EXEC) -lm -lX11
	
clean:
	rm $(EXEC)
