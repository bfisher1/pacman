/**
    @file main.c
    @author Ben Fisher

    Main program run for pacman.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <time.h>
#include "Level.h"
#include "actor.h"

/**
    Starting point of the program.

    @param argc number of command line arguments
    @param argv array of command line arguments

    @return exit status of the program
*/
int main(int argc, char *argv[]){
    Level *level = readLevel("level1.txt");
    if (level == NULL) {
        fprintf(stderr, "Couldn't read level file\n");
        return EXIT_FAILURE;
    }
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);
    //set up random number generator
    time_t t;
    srand((unsigned) time(&t));

    Pacman *pacman = createPacman(1,1);

    float delay = .05;
    WINDOW * win = newwin(level->height + 2, level->width + 1, 0, 0);
    int key;
    clock_t start = clock();
    bool updateScreen = false;
    while (true) {
        
        if( (key = getch()) != ERR  ) {
            if(key ==  KEY_DOWN){
                changePacmanDir(pacman, level, DOWN);
            }
            else if ( key == KEY_UP ){
                changePacmanDir(pacman, level, UP);
            }
            else if(key == KEY_RIGHT ){
                changePacmanDir(pacman, level, RIGHT);
            }
            else if(key ==  KEY_LEFT ){
                changePacmanDir( pacman, level, LEFT);
            }
            updateScreen = true;
        }
        
        if ( readyToUpdate((Actor *) pacman ) ){
            //move stuff
            //draw
            eatTile(pacman, level);
            moveActor((Actor *) pacman, level);
        }

        if( ((float)(clock() - start))/CLOCKS_PER_SEC >= delay ) {
            updateScreen = true;
        }

        if (updateScreen){
            wclear(win);
            drawLevel(level, win);
            drawActor( (Actor *) pacman, win);
            wrefresh(win);
            start = clock();
        }
    }

    freeLevel(level);
    endwin();
    return EXIT_SUCCESS;
}