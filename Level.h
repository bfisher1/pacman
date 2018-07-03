/**
    @file Level.h
    @author Ben Fisher

    Header file for declaring functions associated
    with reading, writing, and drawing a level.
*/
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>
//#include <ncurses.h>

#ifndef LEVEL
#define LEVEL
/**
    Enumeration for the type of tiles in a level.
*/
typedef enum {
    WALL,
    EMPTY,
    FOOD,
    OUTSIDE
} Tile;

/**
    Structure used for storing a 2d array of tiles that make
    up the level.
*/
typedef struct {
    Tile **tiles;
    int width;
    int height;
} Level;

/**
    Creates a level from the given text file.

    @param fileName name of the level file

    @return pointer to the level
*/
Level *readLevel(char *fileName);

/**
    Changes a tile in the level if the new tile is a valid tile.

    @param level pointer to the level being changed
    @param x x coordinate of the tile being changed
    @param y y coordinate of the tile being changed
    @param tile the new value of the tile

    @return true if the tile was changed
*/
bool setLevelTile(Level *level, int x, int y, Tile tile);

/**
    Draws a level to the given window.

    @param level the level being drawn
    @param win the window being drawn
*/
void drawLevel(Level *level, WINDOW *win);

/**
    Returns the tile at a given place in the level, but OUTSIDE
    if outside the dimensions.

    @param level the level being accessed
    @param x the x coordinate of the tile being read
    @param y the y coordinate of the tile being read
*/
Tile getLevelTileAt(Level *level, int x, int y);

/**
    Frees all the memory in a level.

    @param level the level being freed
*/
void freeLevel(Level *level);
#endif /* LEVEL */