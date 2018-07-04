/**
    @file actor.c
    @author Ben Fisher

    Implementation file for "actor.h". Defines functions
    related to actor, ghost, and pacman.
*/
#include "actor.h"

void getGoalCoordinates(Actor *actor, int *x, int *y){
    int goalX = actor->x;
    int goalY = actor->y;
    switch(actor->dir){
        case UP:
            goalY--;
            break;
        case DOWN:
            goalY++;
            break;
        case LEFT:
            goalX--;
            break;
        case RIGHT:
            goalX++;
            break;
        default:
            break;
    }
    *x = goalX;
    *y = goalY;
}

/**
    Behavior code for a ghost that causes it to wonder around.
    The ghost only switches direction when it comes to a junction
    or needs to back up.
    
    @param ghost the ghost that wanders
    @param level the level the ghost wanders in
    @param pacman the pacman in the level (the ghost may chase him)
*/
void wander(Ghost *ghost, Level *level, Pacman *pacman){
    if(ghost->dir == NONE){
        //eventually make random
        ghost->dir = RIGHT;
    }
    int goalX, goalY;
    getGoalCoordinates((Actor *) ghost, &goalX, &goalY);
    if( getLevelTileAt(level, goalX, goalY) == WALL ){
        //eventually make random
        ghost->dir = LEFT;
    }
}

void drawActor(Actor *actor, WINDOW *win){
    mvwaddch(win, actor->y, actor->x, actor->body);
}

void changeDir(Actor *actor, Direction newDir){
    actor->dir = newDir;
}

/**
    Function used to fill an actor's fields. Comparable to the
    constructor for an abstract superclass where Actor is the
    superclass and Ghost or Pacman is the subclass.

    @param x the x coordinate of the actor
    @param y the y coordinate of the actor
    @param speed the speed of the actor
    @param body the anim of the actor
    @param dir the direction of the actor
    @param lastUpdate the last time the actor was updated
*/
void fillActor(Actor *actor, int x, int y, float speed, char body, Direction dir ){
    actor->x = x;
    actor->y = y;
    actor->speed = speed;
    actor->body = body;
    actor->dir = dir;
    actor->lastUpdate = clock();
}

Ghost *createGhost(int x, int y){
    Ghost *ghost = (Ghost *) malloc(sizeof(Ghost));
    fillActor((Actor *) ghost, x, y, .3, 'G', NONE);
    
    //eventually have ghosts that follow player or switch direction randomly, even before wall
    /*
    int ghostType = randInt(0, 2);
    switch(ghostType){
        case 0:
            ghost->decide = wander;
        case 1:
            ghost->decide = aggressive;
        case 2:
            ghost->decide = switchy;
    }
    */
    ghost->decide = wander;
    ghost->chaseRadius = 4;
    return ghost;
}

void freeGhost(Ghost *ghost){
    free(ghost);
}

Pacman *createPacman(int x, int y){
    Pacman *pacman = (Pacman *) malloc(sizeof(Pacman));
    fillActor((Actor *) pacman, x, y, .2, '<', RIGHT);
    pacman->score = 0;
    return pacman;
}

void freePacman(Pacman *pacman){
    free(pacman);
}

void moveActor(Actor *actor, Level *level){
    int goalX, goalY;
    getGoalCoordinates(actor, &goalX, &goalY);
    Tile goalTile = getLevelTileAt(level, goalX, goalY);
    //TODO eventually update for pacman boundaries
    if(goalTile != OUTSIDE && goalTile != WALL){
        actor->x = goalX;
        actor->y = goalY;
    }
    actor->lastUpdate = clock();
}

bool readyToUpdate(Actor *actor){
    return  ( (float) (clock() - actor->lastUpdate) ) / CLOCKS_PER_SEC > actor->speed;
}

void changePacmanDir(Pacman *pacman, Level *level, Direction newDir){
    Direction oldDir = pacman->dir;
    pacman->dir = newDir;
    int goalX, goalY;
    getGoalCoordinates((Actor *) pacman, &goalX, &goalY);
    Tile goalTile = getLevelTileAt(level, goalX, goalY);
    if (goalTile == WALL){
        pacman->dir = oldDir;
    } else{
        switch(pacman->dir){
        case UP:
            pacman->body = 'V';
            break;
        case DOWN:
            pacman->body = '^';
            break;
        case LEFT:
            pacman->body = '>';
            break;
        case RIGHT:
            pacman->body = '<';
            break;
        default:
            break;
        }
    }

}

void eatTile(Pacman *pacman, Level *level){
    if(getLevelTileAt(level, pacman->x, pacman->y) == FOOD){
        setLevelTile(level, pacman->x, pacman->y, EMPTY);
        pacman->score++;
    }
}