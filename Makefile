CC = gcc
CFLAGS = -Wall -std=c99 -g

Pacman : Level.o main.o actor.o util.o
	$(CC) $(CFLAGS) -o $@ $^ -lncurses

Level.o : Level.c Level.h

actor.o : actor.c actor.h

util.o : util.c util.h

main.o : main.c Level.h actor.h Directions.h util.h
