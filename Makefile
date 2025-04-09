CC = g++
CFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -O3 -msse3 -msse2 -msse -mavx2 -mavx

CALC_OPTION = calculate0.cpp 

EXECUTABLE = Man

OPTIMIZATION_0 := 0
OPTIMIZATION_1 := 0
OPTIMIZATION_2 := 0
OPTIMIZATION_3 := 0
OPTIMIZATION_4 := 1

TEST		   := 1

ifeq ($(OPTIMIZATION_0), 1)
	CALC_OPTION = calculate0.cpp
endif

ifeq ($(OPTIMIZATION_1), 1)
	CALC_OPTION = calculate1.cpp
endif

ifeq ($(OPTIMIZATION_2), 1)
	CALC_OPTION = calculate2.cpp
endif

ifeq ($(OPTIMIZATION_3), 1)
	CALC_OPTION = calculate3.cpp
endif

ifeq ($(OPTIMIZATION_4), 1)
	CALC_OPTION = calculate4.cpp
endif

ifeq ($(TEST), 1)
	CFLAGS += -Dtests
endif

all:
	$(CC) $(CALC_OPTION) mandelbrot.cpp $(CFLAGS) -o $(EXECUTABLE)

clean:
	@rm /*.o $(EXECUTABLE)
	
