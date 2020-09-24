#Variables
OPTIONE = -O1
OPTITWO = -O2
OPTITHREE = -O3
CFLAGS = -Wall -pedantic -std=c++11
PARALLELOPTI = -fopenmp
TARGETS = Vect2D.o gameOfLife.o main

.DEFAULT: all

para: Vect2D.op gameOfLife.op mainOP

levelOne: Vect2D.o1 gameOfLife.o1 main1

levelTwo: Vect2D.o2 gameOfLife.o2 main2

levelThree: Vect2D.o3 gameOfLife.o3 main3

all: $(TARGETS)

#Compiling files
#parallel
Vect2D.op: Vect2D.cpp
	g++ $(CFLAGS) $(PARALLELOPTI) -c Vect2D.cpp -o Vect2D.op
gameOfLife.op: gameOfLife.cpp
	g++ $(CFLAGS) $(PARALLELOPTI) -c gameOfLife.cpp -o gameOfLife.op

mainOP: main.cpp Vect2D.op  gameOfLife.op
	g++ $(CFLAGS) $(PARALLELOPTI) Vect2D.op  gameOfLife.op main.cpp -o main

#No Opti
Vect2D.o: Vect2D.cpp
	g++ $(CFLAGS) -c Vect2D.cpp -o Vect2D.o
gameOfLife.o: gameOfLife.cpp
	g++ $(CFLAGS) -c gameOfLife.cpp -o gameOfLife.o

main: main.cpp Vect2D.o  gameOfLife.o
	g++ $(CFLAGS) Vect2D.o  gameOfLife.o main.cpp -o main

#Opt1
Vect2D.o1: Vect2D.cpp
	g++ $(CFLAGS) $(OPTIONE) -c Vect2D.cpp -o Vect2D.o1
gameOfLife.o1: gameOfLife.cpp
	g++ $(CFLAGS) $(OPTIONE) -c gameOfLife.cpp -o gameOfLife.o1

main1: main.cpp Vect2D.o1  gameOfLife.o1
	g++ $(CFLAGS) $(OPTIONE) Vect2D.o1  gameOfLife.o1 main.cpp -o main

#Opti2
Vect2D.o2: Vect2D.cpp
	g++ $(CFLAGS) $(OPTITWO) -c Vect2D.cpp -o Vect2D.o2
gameOfLife.o2: gameOfLife.cpp
	g++ $(CFLAGS) $(OPTITWO) -c gameOfLife.cpp -o gameOfLife.o2

main2: main.cpp Vect2D.o2  gameOfLife.o2
	g++ $(CFLAGS) $(OPTITWO) Vect2D.o2  gameOfLife.o2 main.cpp -o main

#Opti3
Vect2D.o3: Vect2D.cpp
	g++ $(CFLAGS) $(OPTITHREE) -c Vect2D.cpp -o Vect2D.o3
gameOfLife.o3: gameOfLife.cpp
	g++ $(CFLAGS) $(OPTITHREE) -c gameOfLife.cpp -o gameOfLife.o3

main3: main.cpp Vect2D.o3  gameOfLife.o3
	g++ $(CFLAGS) $(OPTITHREE) Vect2D.o3  gameOfLife.o3 main.cpp -o main

#Clean directory
clean:
	rm $(Targets) *.o*