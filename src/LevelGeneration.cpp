//
// Created by nunwan on 17/06/2020.
//
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
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


void LevelGeneration::CreateRectangularRoom(Rectangle roomDimension)
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


void LevelGeneration::place_opening(Tunnelers &tunneler)
{
    bool is_door = 1/(rand() + 1) <= mProbaDoor;
    mToGenerate[tunneler.y][tunneler.x] = is_door?DOOR:FLOOR;
}


bool LevelGeneration::verify_free(Rectangle rectangle)
{
    if (rectangle.x < 0 || rectangle.y < 0) {return false;}
    if (rectangle.x + rectangle.w >= mWidth || rectangle.y + rectangle.h >= mHeight) {return false;}
    for (int x = rectangle.x + 1; x <= rectangle.x + rectangle.w ; ++x) {
        for (int y = rectangle.y + 1 ; y < rectangle.y + rectangle.h; ++y) {
            if (mToGenerate[y][x] != EMPTY) {
                return false;
            }
        }
    }
    return true;
}


void LevelGeneration::run()
{
    auto& tunneler = mTunnelers[0];
    int numberRooms = 0;
    srand(time(NULL));
    Rectangle** first_room;
    Rectangle* room =  create_possible_feature(ROOM, tunneler);
    first_room = &room;
    while (!verify_free(**first_room)) {
        delete  *first_room;
        Rectangle* room = create_possible_feature(ROOM, tunneler);
        first_room = &room;
    }
    push_feature(**first_room);
    while (numberRooms < MAX_ROOMS) {
        for (auto& tunneler : mTunnelers) {
            Rectangle ancient_rectangle = pick_wall(tunneler);
            int feature_type = choose_feature(tunneler, ancient_rectangle);
            Rectangle* new_feature = create_possible_feature(feature_type, tunneler);
            if (verify_free(*new_feature)) {
                std::cout << "libre sa mère " << feature_type<< std::endl;
                push_feature(*new_feature);
                place_opening(tunneler);
                if (feature_type == ROOM) {
                    numberRooms++;
                    tunneler.mLastWasTunnel = 0;
                }
                else if (feature_type == TUNNEL) {
                    tunneler.mLastWasTunnel = 1;
                }
            } else { std::cout << ":( " << feature_type << std::endl;}
            delete new_feature;
        }
    }

}


int **LevelGeneration::getMToGenerate() const
{
    return mToGenerate;
}


Rectangle& LevelGeneration::pick_wall(Tunnelers &tunnelers)
{
    int id_rectangle = rand() % mRectangles.size();
    auto& rectangle_chosen = mRectangles[id_rectangle];
    int chosen_wall;
    if (1/(rand() + 1) < tunnelers.changeDirection) {
        chosen_wall = rand() % 4;
        tunnelers.direction = chosen_wall;
    } else {
        chosen_wall = tunnelers.direction;
    }
    switch (chosen_wall) {
        case DIR_RIGHT:
            tunnelers.x = rectangle_chosen.x + rectangle_chosen.w - 1;
            tunnelers.y = rand() % (rectangle_chosen.h - 2) + rectangle_chosen.y + 1;
            break;
        case DIR_LEFT:
            tunnelers.x = rectangle_chosen.x;
            tunnelers.y = rand() % (rectangle_chosen.h - 2) + rectangle_chosen.y + 1;
            break;
        case DIR_DOWN:
            tunnelers.x = rand() % (rectangle_chosen.w - 2) + rectangle_chosen.x + 1;
            tunnelers.y = rectangle_chosen.y + rectangle_chosen.h - 1;
            break;
        case DIR_UP:
            tunnelers.x = rand() % (rectangle_chosen.w - 2) + rectangle_chosen.x + 1;
            tunnelers.y = rectangle_chosen.y;
            break;
        default:
            break;
    }
    return rectangle_chosen;


}


int LevelGeneration::choose_feature(Tunnelers &tunnelers, Rectangle& ancient_rectangle)
{
    // bool is_room = tunnelers.tunnelWidth != ancient_rectangle.w && tunnelers.tunnelWidth != ancient_rectangle.w;
    // bool is_room = !tunnelers.mLastWasTunnel;
    bool is_room = ancient_rectangle.feature_type == ROOM;
    if (is_room) {
        return TUNNEL;
    } else {
        if (1/rand() < tunnelers.roomProba) {
            return ROOM;
        }
        else {
            return TUNNEL;
        }
    }
}


Rectangle* LevelGeneration::create_possible_feature(int type, Tunnelers &tunnelers)
{
    Rectangle* new_feature = new Rectangle;
    new_feature->feature_type = type;
    if (type == TUNNEL) {
        if (tunnelers.direction % 2) {
            new_feature->w = tunnelers.tunnelWidth;
            new_feature->h = rand() % (MAX_SIZE - MIN_SIZE) + MIN_SIZE;
        }
        else {
            new_feature->h = tunnelers.tunnelWidth;
            new_feature->w = rand() % (MAX_SIZE - MIN_SIZE) + MIN_SIZE;
        }
    }
    else {
        new_feature->w = rand() % (MAX_SIZE - MIN_SIZE) + MIN_SIZE;
        new_feature->h = rand() % (MAX_SIZE - MIN_SIZE) + MIN_SIZE;
    }
    switch (tunnelers.direction) {
        case DIR_RIGHT:
            new_feature->x = tunnelers.x;
            new_feature->y = tunnelers.y - new_feature->h / 2;
            break;
        case DIR_DOWN:
            new_feature->y = tunnelers.y;
            new_feature->x = tunnelers.x - new_feature->w / 2;
            break;
        case DIR_LEFT:
            new_feature->x = tunnelers.x - new_feature->w + 1 ;
            new_feature->y = tunnelers.y - new_feature->h / 2;
            break;
        case DIR_UP:
            new_feature->y = tunnelers.y - new_feature->h + 1;
            new_feature->x = tunnelers.x - new_feature->w / 2;
            break;
        default:
            break;
    }
    return new_feature;
}


void LevelGeneration::push_feature(Rectangle rectangle)
{
    mRectangles.push_back(rectangle);
    int x = rectangle.x;
    int y = rectangle.y;
    int h = rectangle.h;
    int w = rectangle.w;
    for (int i = y+1; i < y+h - 1; ++i) {
        for (int j = x+1; j < x+w - 1 ; ++j) {
            mToGenerate[i][j] = FLOOR;
        }
    }
    if (rectangle.feature_type == TUNNEL){
        for (int i = x; i < x+w; ++i) {
            mToGenerate[y][i] = WALL_TUNNEL;
            mToGenerate[y+h-1][i] = WALL_TUNNEL;
        }
        for (int i = y; i < y+h; ++i) {
            mToGenerate[i][x] = WALL_TUNNEL;
            mToGenerate[i][x+w-1] = WALL_TUNNEL;
        }
        return;
    }
    for (int i = x; i < x+w; ++i) {
        mToGenerate[y][i] = WALL;
        mToGenerate[y+h-1][i] = WALL;
    }
    for (int i = y; i < y+h; ++i) {
        mToGenerate[i][x] = WALL;
        mToGenerate[i][x+w-1] = WALL;
    }
    if (LOG_MAP) {
        write_log_map();
    }
}


void LevelGeneration::write_log_map()
{
    std::ofstream os("log_map.txt");
    if (os.is_open()) {
        os << "\n";
        os << "============ new step ======== \n";
        for (int i = 0; i < mHeight; ++i) {
            for (int j = 0; j < mWidth; ++j) {
                os << mToGenerate[i][j];
            }
            os << "\n";
        }
    }


}
