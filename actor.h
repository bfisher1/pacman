/**
    @file actor.h
    @author Ben Fisher

    Header file containing declarations for functions involved with
    actors. Actors in pacman are characters like pacman and the
    ghosts. Actor acts as an abstract super class for pacman and ghost.
*/
#include <ncurses.h>
#include "Directions.h"
#include <stdbool.h>
#include "Level.h"
#include <stdlib.h>
#include <time.h>
#include "util.h"

#ifndef ACTOR
#define ACTOR
/**
    Structure for an actor, containing coordinates, speed,
    direction, and a display character, and a timestamp
    for when the actor was last updated.
*/
typedef struct ActorStruct {
    int x;
    int y;
    float speed;
    char body;
    Direction dir;
    clock_t lastUpdate;
} Actor;

/**
    Structure for Pacman, extending the Actor struct.
    Aditionally, it contains how many lives pacman has left,
    whether he is immune to ghosts, and a score counter.
*/
typedef struct {
    int x;
    int y;
    float speed;
    char body;
    Direction dir;
    clock_t lastUpdate;
    int lives;
    bool isImmune;
    int score;
} Pacman;

/**
    Structure for a Ghost, extending the Actor struct.
    Also contains a pointer to a function that decides the ghost's
    behavior (some ghosts follow pacman, some wander around randomly),
    and a chase radius for ghosts that chase pacman.
*/
typedef struct GhostStruct {
    int x;
    int y;
    float speed;
    char body;
    Direction dir;
    clock_t lastUpdate;
    void (*decide)(struct GhostStruct *ghost, Level *level, Pacman *pacman);
    int chaseRadius;
} Ghost;


/**
    Creates a ghost at the given coordinates.

    @param x the x coordinate of the ghost
    @param y the y coordinate of the ghost
*/
Ghost *createGhost(int x, int y);

/**
    Frees the ghost from memory.

    @param ghost the ghost being freed
*/
void freeGhost(Ghost *ghost);

/**
    Creates pacman at the given coordinates.

    @param x the x coordinate of pacman
    @param y the y coordinate of pacman
*/
Pacman *createPacman(int x, int y);

/**
    Frees pacman from memory.

    @param pacman the pacman being freed
*/
void freePacman(Pacman *pacman);

/**
    Moves an actor in the direction it is headed. The actor won't
    move if a wall is in the way.

    @param actor the actor moving
    @param level the level the actor is moving in
*/
void moveActor(Actor *actor, Level *level);

/**
    Determines if the actor is ready to be updated.

    @param the actor being checked
    @return true if the actor is ready to update, false if not
*/
bool readyToUpdate(Actor *actor);

/**
    Draws an actor to the given window.

    @param actor the actor being drawn
    @param win the window the actor is drawn to
*/
void drawActor(Actor *actor, WINDOW *win);

/**
    Changes pacman's direction if the direction is open and updates
    his animation.

    @param pacman the pacman changing direction
    @param level the level pacman is changing direction in
           (pacman can't turn to face a wall next to him)
    @param newDir the direction pacman tries to turn to
*/
void changePacmanDir(Pacman *pacman, Level *level, Direction newDir);

/**
    Pacman eats food if he is on a tile with food. His score counter
    is updated.

    @param pacman the pacman who eats the tile
    @param level the level pacman is in
*/
void eatTile(Pacman *pacman, Level *level);

/**
    Determines if 2 actors are colliding.

    @param actor1 first actor that might be colliding with the other
    @param actor2 second actor that might be colliding with the other

    @return true if the actors are colliding, false if not
*/
bool areColliding(Actor *actor1, Actor *actor2);
#endif /* ACTOR */