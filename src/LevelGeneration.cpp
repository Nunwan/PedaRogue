//
// Created by nunwan on 17/06/2020.
//
#include <stdlib.h>
#include <time.h>
#include "LevelGeneration.hpp"

LevelGeneration::LevelGeneration(int height_map, int width_map)
{
    mProbaDoor = PROBA_DOOR;
    // Create the first tunnelers
    srand(time(NULL));
    int x_dad = rand() % 15 + 5;
    int y_dad = rand() % 15 + 5;
    Tunnelers dadTunnelers = {x_dad, y_dad, 0, CHANGE_DIRECTION_PARENT, ROOM_PROBA_PARENT, TUNNEL_WIDTH_PARENT};
    mTunnelers.push_back(dadTunnelers);

    // Initialise map
    mWidth = width_map;
    mHeight = height_map;
    mToGenerate = new int*[height_map];
    for (int i = 0; i < height_map; ++i) {
       mToGenerate[i] = new int[width_map];
    }

    for (int i = 0; i < height_map; ++i) {
        for (int j = 0; j < width_map; ++j) {
            mToGenerate[i][j] = 0;
        }
    }
}


LevelGeneration::~LevelGeneration()
{
    for (int i = 0; i < mHeight; ++i) {
        delete mToGenerate[i];
    }
    delete mToGenerate;
}


void LevelGeneration::CreateRectangularRoom(int x, int y, int w, int h)
{
    for (int i = y+1; i < y+h; ++i) {
       for (int j = x+1; j < x+w; ++j) {
           mToGenerate[i][j] = FLOOR;
       }
    }
    for (int i = x; i <= x+w; ++i) {
        mToGenerate[i][y] = WALL;
        mToGenerate[i][y+h] = WALL;
    }
    for (int i = y; i <= y+h; ++i) {
        mToGenerate[x][i] = WALL;
        mToGenerate[x+w][i] = WALL;
    }
}


void LevelGeneration::place_opening(int x, int y)
{
    srand(time(NULL));
    bool is_door = 1/(rand() + 1) <= mProbaDoor;
    mToGenerate[x][y] = is_door?DOOR : FLOOR;
}


