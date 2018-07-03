/**
    @file Level.c
    @author Ben Fisher

    Implementation file for functions declared in Level.h.
    Contains functions for reading a level from a file,
    drawing the level, and getting the value of a cell in it.
*/
#include "Level.h"


Level *readLevel(char *fileName){
    FILE *f = fopen(fileName, "r");
    if(f == NULL){
        fprintf(stderr, "Error reading level file\n");
        return NULL;
    }
    int ch;
    int cols = 0;
    while( (ch = fgetc(f) ) != EOF && ch != '\n' ){
        cols++;
    }

    rewind(f);

    Level *level = (Level *) malloc(sizeof(Level));
    int cap = 5;
    Tile **tiles = (Tile **) malloc(cap  * sizeof(Tile * ));
    tiles[0] = (Tile *) malloc( sizeof(Tile) * cols);
    int row = 0;
    int col = 0;
    while( (ch = fgetc(f) ) != EOF ){
        

        if(ch == '\n'){
            row++;
            col = 0;
            tiles[row] = (Tile *) malloc( sizeof(Tile) * cols );
        }
        else {
            //printf("%d %d\n", row, col);
            if (ch == '#') {
                tiles[row][col] = WALL;
            }
            else if ( ch == '.' ) {
                tiles[row][col] = FOOD;
            }
            else if ( ch == ' ' ) {
                tiles[row][col] = EMPTY;
            }
            col++;
        }
        /*
        if(col > cols) free everything
        */
        //expland capacity of tile array if too big
        if (row >= cap - 1) {
            cap *= 2;
            Tile **newTiles = (Tile **) malloc( sizeof(Tile *) * cap );
            for(int i = 0; i <= row; i++){
                newTiles[i] = tiles[i];
            }
            free(tiles);
            tiles = newTiles;
            //printf("Doubled\n");
        }
        
    }

    level->tiles = tiles;
    fclose(f);
    level->width = cols;
    level->height = row + 1;
    return level;
}
bool setLevelTile(Level *level, int x, int y, Tile tile){
    if (x < 0 || x >= level->width || y < 0 || y >= level->height) {
        return false;
    }
    level->tiles[y][x] = tile;
    return true;
}
void drawLevel(Level *level, WINDOW *win){
    for(int i = 0; i < level->height; i++){
        for(int j = 0; j < level->width; j++){
            Tile tile = level->tiles[i][j];
            char tileChar;
            switch (tile) {
                case WALL:
                    tileChar = 'W';
                    break;
                case FOOD:
                    tileChar = '.';
                    break;
                case EMPTY:
                    tileChar = ' ';
                    break;
                default:
                    tileChar = '?';
                    break;
            }
            mvwaddch(win, i, j, tileChar);
        }
    }
    
}
Tile getLevelTileAt(Level *level, int x, int y){
    if (x < 0 || x >= level->width || y < 0 || y >= level->height) {
        return OUTSIDE;
    }
    return level->tiles[y][x];
}

void freeLevel(Level *level){
    for(int i = 0; i < level->height; i++){
        free(level->tiles[i]);
    }
    free(level->tiles);
    free(level);
}