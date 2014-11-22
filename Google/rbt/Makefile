# !/usr/bin/make
CC=g++
CFLAGS=-g -Wall -std=c++0x
LFLAGS=

all: node.o rbt.o main.cpp
	${CC} ${CFLAGS} ${LFLAGS} node.o rbt.o main.cpp -o rbt

node.o: node.h node.cpp
	${CC} ${CFLAGS} -c node.cpp

rbt.o: rbt.h rbt.cpp
	${CC} ${CFLAGS} -c rbt.cpp

clean: .
	rm *.o
