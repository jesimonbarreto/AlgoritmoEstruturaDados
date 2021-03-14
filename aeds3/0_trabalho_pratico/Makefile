#makefile
 
all: tp0
 
tp0: tp0.o Queue.o Graph.o
	gcc	-o	tp0	tp0.o	Queue.o	Graph.o
 
tp0.o: tp0.c Queue.h Graph.h
	gcc	-o	tp0.o	-c tp0.c	-W	-Wall
 
Queue.o: Queue.c Queue.h
	gcc	-o	Queue.o	Queue.c	-c	-W	-Wall

Graph.o: Graph.c Graph.h
	gcc	-o	Graph.o	Graph.c	-c	-W	-Wall
 
clean:
	rm	-rf	*.o	*~	tp0