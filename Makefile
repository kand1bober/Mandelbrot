CC = g++
CFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

EXECUTABLE = Man

all:
	
	$(CC) calculate.cpp mandelbrot.cpp $(CFLAGS) -o $(EXECUTABLE)

clean:
	@rm /*.o $(EXECUTABLE)

	