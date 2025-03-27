CC = g++
CFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all:
	
	$(CC) draw.cpp $(CFLAGS) -o drawer 

clean:
	rm drawer
	