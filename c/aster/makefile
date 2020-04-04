EXEC = aster

$(EXEC): aster.c gfx.c gfx.h
	gcc aster.c gfx.c -o $(EXEC) -lm -lX11
	
clean:
	rm $(EXEC)
