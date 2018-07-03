CC = gcc
CFLAGS = -Wall -std=c99 -g

Pacman : Level.o main.o
	$(CC) $(CFLAGS) -o $@ $^ -lncurses

Level.o : Level.c Level.h

main.o : main.c Level.h
