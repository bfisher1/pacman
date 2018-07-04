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
#include "util.h"

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

    int pacmanStartX = 1;
    int pacmanStartY = 1;
    
    Pacman *pacman = createPacman(pacmanStartX, pacmanStartY);
    int ghostNumber = 4;
    Ghost *ghosts[ghostNumber];
    for (int i = 0; i < ghostNumber; i++) {
        ghosts[i] = createGhost(10, 3);
    }

    float delay = .05;
    WINDOW * win = newwin(level->height + 2, level->width + 1, 0, 0);
    int key;
    clock_t start = clock();
    bool updateScreen = false;
    bool gameOver = false;
    int goalScore = countFood(level);
    while (!gameOver) {
        
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

        for (int i = 0; i < ghostNumber; i++) {
            if (readyToUpdate( (Actor *) ghosts[i]) ){
                ghosts[i]->decide(ghosts[i], level, pacman);
                moveActor((Actor *) ghosts[i], level);
                break;
            }
        }
        
        if ( readyToUpdate((Actor *) pacman ) ){
            eatTile(pacman, level);
            moveActor((Actor *) pacman, level);
        }

        for (int i = 0; i < ghostNumber; i++) {
            if (areColliding( (Actor *) pacman, (Actor *) ghosts[i] )) {
                pacman->lives--;
                pacman->x = pacmanStartX;
                pacman->y = pacmanStartY;
                
                wclear(win);
                drawLevel(level, win);
                for (int i = 0; i < ghostNumber; i++) {
                    drawActor( (Actor *) ghosts[i], win );
                }
                for (int i = 0; i < pacman->lives; i++) {
                    mvwaddch(win, 10, i, '<');
                }
                wrefresh(win);
                delayMs(1000);
                if (pacman->lives <= 0) {
                    gameOver = true;
                }
            }
        }

        if (pacman->score == goalScore) {
            gameOver = true;
        }

        if( ((float)(clock() - start))/CLOCKS_PER_SEC >= delay ) {
            updateScreen = true;
        }

        if (updateScreen) {
            wclear(win);
            drawLevel(level, win);
            for (int i = 0; i < ghostNumber; i++) {
                drawActor( (Actor *) ghosts[i], win );
            }
            drawActor( (Actor *) pacman, win);
            for (int i = 0; i < pacman->lives; i++) {
                mvwaddch(win, 10, i, '<');
            }
            wrefresh(win);
            start = clock();
        }
    }
    int finalScore = pacman->score;
    freePacman(pacman);
    for (int i = 0; i < ghostNumber; i++) {
        freeGhost(ghosts[i]);
    }
    freeLevel(level);
    endwin();
    if (finalScore == goalScore) {
        printf("YOU WIN!\n");
    }
    else {
        printf("GAME OVER. SCORE: %d\n", finalScore);
    }
    
    return EXIT_SUCCESS;
}