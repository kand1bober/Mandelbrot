CC = g++
CFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

EXECUTABLE = Man

all:
	
	$(CC) -O2 calculate2.cpp mandelbrot.cpp $(CFLAGS) -o $(EXECUTABLE)

clean:
	@rm /*.o $(EXECUTABLE)
	
