# !/usr/bin/make
CC=g++
CFLAGS=-g -Wall -std=c++0x
LFLAGS=

all: node.o bst.o main.cpp
	${CC} ${CFLAGS} ${LFLAGS} node.o bst.o main.cpp -o bst

node.o: node.h node.cpp
	${CC} ${CFLAGS} -c node.cpp

bst.o: bst.h bst.cpp
	${CC} ${CFLAGS} -c bst.cpp

clean: .
	rm *.o
