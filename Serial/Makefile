#Variables
CFLAGS = -Wall -pedantic -std=c++11
TARGETS = Vect2D.o gameOfLife.o main
VIS = visualisation.o
PYTHONVIS = -I/usr/include/python2.7 -lpython
.DEFAULT: all

pyth: $(TARGETS) $(VIS)

all: $(TARGETS)

#Compiling files
Vect2D.o: Vect2D.cpp
	g++ $(CFLAGS) -c Vect2D.cpp -o Vect2D.o
gameOfLife.o: gameOfLife.cpp
	g++ $(CFLAGS) -c gameOfLife.cpp -o gameOfLife.o
visualisation.o: visualisation.cpp matplotlibcpp.h
	g++ $(CFLAGS) -c visualisation.cpp -o visualisation.o $(PYTHONVIS)


main: main.cpp Vect2D.o  gameOfLife.o
	g++ $(CFLAGS) Vect2D.o  gameOfLife.o main.cpp -o main

#Clean directory
clean:
	rm $(Targets) *.o
