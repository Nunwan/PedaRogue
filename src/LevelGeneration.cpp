//
// Created by nunwan on 17/06/2020.
//
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "LevelGeneration.hpp"

#define min(a,b) a<=b?a:b
#define max(a,b) a>=b?a:b

LevelGeneration::LevelGeneration(int height_map, int width_map)
{
    mProbaDoor = PROBA_DOOR;
    // Create the first tunnelers
    srand(time(NULL));
    int x_dad = rand() % 15 + 2;
    int y_dad = rand() % 15 + 2;
    Tunnelers dadTunnelers = {x_dad, y_dad, 0, CHANGE_DIRECTION_PARENT, ROOM_PROBA_PARENT, TUNNEL_HALFWIDTH_PARENT};
    mTunnelers.push_back(dadTunnelers);

    // Initialise map
    mWidth = width_map;
    mHeight = height_map;
    mToGenerate = new int *[height_map];
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
        delete[] mToGenerate[i];
    }
    delete[] mToGenerate;
}


void LevelGeneration::CreateRectangularRoom(Dimension roomDimension)
{
    int x = roomDimension.x;
    int y = roomDimension.y;
    int h = roomDimension.h;
    int w = roomDimension.w;
    for (int i = y+1; i < y+h; ++i) {
       for (int j = x+1; j < x+w; ++j) {
           mToGenerate[i][j] = FLOOR;
       }
    }
    for (int i = x; i <= x+w; ++i) {
        mToGenerate[y][i] = WALL;
        mToGenerate[y+h][i] = WALL;
    }
    for (int i = y; i <= y+h; ++i) {
        mToGenerate[i][x] = WALL;
        mToGenerate[i][x+w] = WALL;
    }
}


void LevelGeneration::place_opening(int tunneler_id)
{
    auto tunneler = mTunnelers[tunneler_id];
    bool is_door = 1/(rand() + 1) <= mProbaDoor;
    mToGenerate[tunneler.y][tunneler.x] = is_door?DOOR:FLOOR;
    /*if (tunneler.direction % 2) {
        int negative = tunneler.direction / 2 == 0 ? 1 : -1;
        for (int x = tunneler.x - tunneler.tunnelHalfWidth; x < tunneler.x + tunneler.tunnelHalfWidth; ++x) {
            mToGenerate[tunneler.y + negative*1][x] = FLOOR;
        }
    }
    else {
        int negative = tunneler.direction / 2 == 0 ? 1 : -1;
        for (int y = tunneler.y - tunneler.tunnelHalfWidth; y < tunneler.y + tunneler.tunnelHalfWidth; ++y) {
            mToGenerate[y][tunneler.x + negative*1] = FLOOR;
        }
    }
    if (is_door) {
        if (tunneler.direction % 2) {
            int negative = tunneler.direction / 2 == 0 ? 1 : -1;
            int x_door = tunneler.x - rand() % (2 * tunneler.tunnelHalfWidth ) + tunneler.tunnelHalfWidth;
            mToGenerate[tunneler.y + negative*1][x_door] = DOOR;
        }
        else {
            int negative = tunneler.direction / 2 == 0 ? 1 : -1;
            int y_door = tunneler.y - rand() % (2 * tunneler.tunnelHalfWidth ) + tunneler.tunnelHalfWidth;
            mToGenerate[y_door][tunneler.x + negative*1] = DOOR;
        }
    }*/
}


void LevelGeneration::CreateTunnel(Dimension dimension, int direction)
{
    if (direction % 2 == 0) {
        for (int y = dimension.y - dimension.h + 2; y < dimension.y + dimension.h - 1; ++y) {
            for (int x = dimension.x + 1; x <= dimension.x + dimension.w+ 1; ++x) {
                mToGenerate[y][x] = FLOOR;
            }
        }
        for (int x = dimension.x + 1; x <= dimension.x + dimension.w +1 ; ++x) {
            if (mToGenerate[dimension.y - dimension.h + 1][x] != FLOOR) {
                mToGenerate[dimension.y - dimension.h + 1][x] = WALL_TUNNEL;
            }
            if (mToGenerate[dimension.y + dimension.h - 1][x] != FLOOR) {
                mToGenerate[dimension.y +dimension.h - 1][x] = WALL_TUNNEL;
            }
        }
    }
    else {
        for (int x = dimension.x - dimension.w + 2; x < dimension.x + dimension.w - 1; ++x) {
            for (int y = dimension.y + 1; y <= dimension.y + dimension.h + 1; ++y) {
                mToGenerate[y][x] = FLOOR;
            }
        }
        for (int y = dimension.y + 1; y <= dimension.y + dimension.h +1 ; ++y) {
            if (mToGenerate[y][dimension.x - dimension.w + 1] != FLOOR) {
                mToGenerate[y][dimension.x - dimension.w + 1] = WALL_TUNNEL;
            }
            if (mToGenerate[y][dimension.x + dimension.w - 1] != FLOOR) {
                mToGenerate[y][dimension.x + dimension.w - 1] = WALL_TUNNEL;
            }
        }
    }
}


bool LevelGeneration::verify_free(Dimension rectangle)
{
    for (int x = rectangle.x; x <= rectangle.x + rectangle.w ; ++x) {
        for (int y = rectangle.y; y < rectangle.y + rectangle.h; ++y) {
            if (x >= mWidth || y >= mHeight || x < 0 || y < 0)  {return false;}
            if (mToGenerate[y][x] != WALL_TUNNEL && mToGenerate[y][x] != EMPTY) {
                return false;
            }
        }
    }
    return true;
}


void LevelGeneration::forward_until(int tunneler, int limite)
{
    int compteur = 0;
    if (limite == -1) {
        limite = max(2 * mWidth, 2 * mHeight);
    }
    auto& theTunneler = mTunnelers[tunneler];
    if (theTunneler.direction == DIR_DOWN) {
        while (compteur < limite && theTunneler.y + 1 < mHeight && mToGenerate[theTunneler.y + 1][theTunneler.x] != 0) {
            theTunneler.y++;
            compteur++;
        }
    }
    else if (theTunneler.direction == DIR_RIGHT){
        while (compteur < limite && theTunneler.x + 1< mWidth && mToGenerate[theTunneler.y][theTunneler.x + 1] != 0) {
            theTunneler.x++;
            compteur++;
        }
    }
    else if (theTunneler.direction == DIR_UP) {
        while (compteur < limite && theTunneler.y > 0 && mToGenerate[theTunneler.y - 1][theTunneler.x] != 0) {
            theTunneler.y--;
            compteur++;
        }
    }
    else if (theTunneler.direction == DIR_LEFT){
        while (compteur < limite && theTunneler.x > 0 && mToGenerate[theTunneler.y][theTunneler.x - 1] != 0) {
            theTunneler.x--;
            compteur++;
        }
    }
}


void LevelGeneration::run()
{
    auto& tunneler = mTunnelers[0];
    std::cout << tunneler.x << " "<< tunneler.y << std::endl;
    int numberRooms = 0;
    srand(time(NULL));
    PlaceRoom(0);
    forward_until(0);
    place_opening(0);
    mTunnelers[0].mLastWasTunnel = 0;
    while (numberRooms < MAX_ROOMS) {
        std::cout << "debut\n";
        int number_stop = 0;
        int direction = 0;
        for (int i = 0; i < mTunnelers.size(); i++)  {
            auto& tunneler = mTunnelers[i];
            if (tunneler.can_continue) {
                if (tunneler.mLastWasTunnel && 1/rand() < tunneler.roomProba) {
                    tunneler.can_continue = PlaceRoom(i);
                    if (tunneler.can_continue) {
                        forward_until(i, 1);
                        place_opening(i);
                        tunneler.mLastWasTunnel = 0;
                        forward_until(i);
                        place_opening(i);
                        numberRooms++;
                    }
                    std::cout << "room " << tunneler.can_continue << std::endl;
                }
                else {
                    tunneler.can_continue = PlaceTunnel(i);
                    forward_until(i);
                    tunneler.mLastWasTunnel = 1;
                    std::cout << "Tunnel \n";
                }
                if (1/rand() < tunneler.changeDirection) {
                    if (rand() % 2) {
                        tunneler.direction = (tunneler.direction + 1) % 4;
                    }
                    else {
                        tunneler.direction = (tunneler.direction - 1) % 4;
                    }
                    std::cout << "changedir \n";
                    forward_until(i);
                }
                mToGenerate[tunneler.y][tunneler.x] = 6;
            }
            else {
                number_stop++;
            }
        }
        if (number_stop == mTunnelers.size()) {
            break;
        }
    }

}


int LevelGeneration::PlaceTunnel(int tunneler)
{
    Tunnelers theTunneler = mTunnelers[tunneler];
    Dimension futureTunnel;
    int try_number = 0;
    do {
        if (theTunneler.direction == 1) {
            int x_off = theTunneler.tunnelHalfWidth;
            futureTunnel.x = theTunneler.x - x_off;
            futureTunnel.y = theTunneler.y + 1;
            futureTunnel.w = 2 * x_off + 1;
            futureTunnel.h = rand() % MAX_DEPTH_TUNNEL + MIN_SIZE;
        }
        else if (theTunneler.direction == 0) {
            int y_off = theTunneler.tunnelHalfWidth;
            futureTunnel.y = theTunneler.y - y_off;
            futureTunnel.x = theTunneler.x + 1;
            futureTunnel.h = 2 * y_off + 1;
            futureTunnel.w = rand() % MAX_DEPTH_TUNNEL+ MIN_SIZE;
        }
        else if (theTunneler.direction == 2) {
            int y_off = theTunneler.tunnelHalfWidth;
            futureTunnel.y = theTunneler.y - y_off;
            futureTunnel.h = 2 * y_off - 1;
            futureTunnel.w = rand() % MAX_DEPTH_TUNNEL+ MIN_SIZE;
            futureTunnel.x = theTunneler.x - futureTunnel.w;
        }
        else {
            int x_off = theTunneler.tunnelHalfWidth;
            futureTunnel.x = theTunneler.x - x_off;
            futureTunnel.w = 2 * x_off + 1;
            futureTunnel.h = rand() % MAX_DEPTH_TUNNEL+ MIN_SIZE;
            futureTunnel.y = theTunneler.y - futureTunnel.h;
        }
        try_number++;
    } while (try_number < 10 && !verify_free(futureTunnel));
    if (try_number == 10) {return 0;}
    // Return to tunnel coordinate
    if (theTunneler.direction == DIR_RIGHT) {
        futureTunnel.x = theTunneler.x;
        futureTunnel.y = theTunneler.y;
    }
    if (theTunneler.direction % 2 == 0) {
        futureTunnel.h = theTunneler.tunnelHalfWidth;
    }
    else {
        futureTunnel.w = theTunneler.tunnelHalfWidth;
    }
    CreateTunnel(futureTunnel, theTunneler.direction);
    return 1;
}


int LevelGeneration::PlaceRoom(int tunneler)
{
    Tunnelers theTunneler = mTunnelers[tunneler];
    Dimension futureRoom;
    int try_number = 0;
    do {
        if (theTunneler.direction == 1) {
            int x_off = rand() % 10 + min(theTunneler.x, MIN_SIZE);
            futureRoom.x = theTunneler.x - x_off;
            futureRoom.y = theTunneler.y + 1;
            futureRoom.w = rand() % MAX_SIZE + x_off + 1;
            futureRoom.h = rand() % MAX_SIZE + MIN_SIZE;
        }
        else if (theTunneler.direction == 0) {
            int y_off = rand() % 10 + min(theTunneler.y, MIN_SIZE);
            futureRoom.y = theTunneler.y - y_off;
            futureRoom.x = theTunneler.x + 1;
            futureRoom.h = rand() % MAX_SIZE + y_off + 1;
            futureRoom.w = rand() % MAX_SIZE + MIN_SIZE;
        }
        else if (theTunneler.direction == 2) {
            int y_off = rand() % 10 + min(theTunneler.y, MIN_SIZE);
            futureRoom.y = theTunneler.y - y_off;
            futureRoom.h = rand() % MAX_SIZE + y_off + 1;
            futureRoom.w = rand() % MAX_SIZE + MIN_SIZE;
            futureRoom.x = theTunneler.x - futureRoom.w;
        }
        else {
            int x_off = rand() % 10 + min(theTunneler.x, MIN_SIZE);
            futureRoom.x = theTunneler.x - x_off;
            futureRoom.w = rand() % MAX_SIZE + x_off + 1;
            futureRoom.h = rand() % MAX_SIZE + MIN_SIZE;
            futureRoom.y = theTunneler.y - futureRoom.h;
        }
        try_number++;
    } while (try_number < 10 && !verify_free(futureRoom));
    if (try_number == 10) {return 0;}
    theTunneler.x--;
    CreateRectangularRoom(futureRoom);
    return 1;
}


int **LevelGeneration::getMToGenerate() const
{
    return mToGenerate;
}
