CC = g++
CFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

EXECUTABLE = Man

all:
	
	$(CC) -O2 -msse3 -msse2 -msse -mavx2 -mavx calculate3.cpp mandelbrot.cpp $(CFLAGS) -o $(EXECUTABLE)

clean:
	@rm /*.o $(EXECUTABLE)
	
