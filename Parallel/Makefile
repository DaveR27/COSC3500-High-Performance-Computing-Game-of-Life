#Variables
OPTIONE = -O1
OPTITWO = -O2
OPTITHREE = -O3
CFLAGS = -Wall -pedantic -std=c++11
PARALLELOPTI = -fopenmp
TARGETS = Vect2D.o gameOfLife.o main

.DEFAULT: all

para3: Vect2D.op3 gameOfLife.op3 mainOP3

para2: Vect2D.op2 gameOfLife.op2 mainOP2

para1: Vect2D.op1 gameOfLife.op1 mainOP1

para: Vect2D.op gameOfLife.op mainOP

#Compiling files
#parallel Opti 3
Vect2D.op3: Vect2D.cpp
	g++ $(CFLAGS) $(PARALLELOPTI) $(OPTITHREE) -c Vect2D.cpp -o Vect2D.op3
gameOfLife.op3: gameOfLife.cpp
	g++ $(CFLAGS) $(PARALLELOPTI) $(OPTITHREE) -c gameOfLife.cpp -o gameOfLife.op3

mainOP3: main.cpp Vect2D.op3  gameOfLife.op3
	g++ $(CFLAGS) $(PARALLELOPTI) $(OPTITHREE) Vect2D.op3  gameOfLife.op3 main.cpp -o main

#parallel Opti 2
Vect2D.op2: Vect2D.cpp
	g++ $(CFLAGS) $(PARALLELOPTI) $(OPTITWO) -c Vect2D.cpp -o Vect2D.op2
gameOfLife.op2: gameOfLife.cpp
	g++ $(CFLAGS) $(PARALLELOPTI) $(OPTITWO) -c gameOfLife.cpp -o gameOfLife.op2

mainOP2: main.cpp Vect2D.op2  gameOfLife.op2
	g++ $(CFLAGS) $(PARALLELOPTI) $(OPTITWO) Vect2D.op2  gameOfLife.op2 main.cpp -o main

#parallel Opti 1
Vect2D.op1: Vect2D.cpp
	g++ $(CFLAGS) $(PARALLELOPTI) $(OPTIONE) -c Vect2D.cpp -o Vect2D.op1
gameOfLife.op1: gameOfLife.cpp
	g++ $(CFLAGS) $(PARALLELOPTI) $(OPTIONE) -c gameOfLife.cpp -o gameOfLife.op1

mainOP1: main.cpp Vect2D.op1  gameOfLife.op1
	g++ $(CFLAGS) $(PARALLELOPTI) $(OPTIONE) Vect2D.op1  gameOfLife.op1 main.cpp -o main

#parallel
Vect2D.op: Vect2D.cpp
	g++ $(CFLAGS) $(PARALLELOPTI) -c Vect2D.cpp -o Vect2D.op
gameOfLife.op: gameOfLife.cpp
	g++ $(CFLAGS) $(PARALLELOPTI) -c gameOfLife.cpp -o gameOfLife.op

mainOP: main.cpp Vect2D.op  gameOfLife.op
	g++ $(CFLAGS) $(PARALLELOPTI) Vect2D.op  gameOfLife.op main.cpp -o main


#Clean directory
clean:
	rm $(Targets) *.o*