CFLAGS=-std=c++11 -g

all: list

list: main.cpp LinkedList.h LinkedListInterface.h
	g++ $(CFLAGS) main.cpp -o Lab6