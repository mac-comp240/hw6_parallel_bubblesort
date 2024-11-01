# Makefile for Homework 6: Parallel
# Susan Fox
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c99
LFLAGS = -fopenmp

all: bubble

bubble: bubblesort.c
	${CC} ${CFLAGS} -o bubble bubblesort.c $(LFLAGS)

clean:
	rm -f bubble
