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

    float delay = .05;
    WINDOW * win = newwin(level->height + 2, level->width + 1, 0, 0);
    int key;
    clock_t start = clock();
    while (true) {
        
        if( (key = getch()) != ERR  ) {
            /*
            if(key ==  KEY_DOWN){
                changeSnakeDir(snake, DOWN);
            }
            else if ( key == KEY_UP ){
                changeSnakeDir(snake, UP);
            }
            else if(key == KEY_RIGHT ){
                changeSnakeDir(snake, RIGHT);
            }
            else if(key ==  KEY_LEFT ){
                changeSnakeDir(snake, LEFT);
            }
            */
        }
        
        if( ((float)(clock() - start))/CLOCKS_PER_SEC >= delay ){
            wclear(win);
            //move stuff
            //draw
            drawLevel(level, win);
            wrefresh(win);
            
            start = clock();
        }
    }

    freeLevel(level);
    endwin();
    return EXIT_SUCCESS;
}