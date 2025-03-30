CC = g++
CFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

EXECUTABLE = Man

all:
	
	$(CC) -o2 calculate1.cpp mandelbrot.cpp $(CFLAGS) -o $(EXECUTABLE)

clean:
	@rm /*.o $(EXECUTABLE)

	