//
// Created by nunwan on 17/06/2020.
//
#include <random>
#include <time.h>
#include <iostream>
#include <fstream>
#include "LevelGeneration.hpp"

#define min(a,b) a<=b?a:b
#define max(a,b) a>=b?a:b

LevelGeneration::LevelGeneration(int height_map, int width_map, float probaMonster, float probaObject,
                                 int maxMonster, int maxObject)
{
    mProbaDoor = PROBA_DOOR;
    // Create the first tunnelers
    srand(time(NULL));
    int x_dad = rand() % 15 + 2;
    int y_dad = rand() % 15 + 2;

    Tunnelers dadTunnelers = {x_dad, y_dad, 0, CHANGE_DIRECTION_PARENT, ROOM_PROBA_PARENT, TUNNEL_HALFWIDTH_PARENT, PROBA_LIGHT};
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
    mProbaMonster = probaMonster;
    mProbaObjects = probaObject;
    mMaxMonsters = maxMonster;
    mMaxObjects = maxObject;
}

LevelGeneration::~LevelGeneration()
{
    for (int i = 0; i < mHeight; ++i) {
        delete[] mToGenerate[i];
    }
    delete[] mToGenerate;
}


void LevelGeneration::place_opening(Tunnelers &tunneler)
{
    bool is_door = ((double) rand() / (RAND_MAX)) <= mProbaDoor;
    mToGenerate[tunneler.y][tunneler.x] = is_door?DOOR:FLOOR;
}


bool LevelGeneration::verify_free(Rectangle rectangle, int offset_x, int offset_y)
{
    if (rectangle.x - offset_x < 0 || rectangle.y  - offset_y < 0) {return false;}
    if (rectangle.x + rectangle.w + offset_x >= mWidth || rectangle.y + rectangle.h  + offset_y >= mHeight) {return false;}
    for (int x = rectangle.x + 1 - offset_x; x <= rectangle.x + rectangle.w + offset_x; ++x) {
        for (int y = rectangle.y + 1 - offset_y; y < rectangle.y + rectangle.h + offset_y; ++y) {
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
    delete room;
    int tried = 0;
    while (tried < 1000 && numberRooms < MAX_ROOMS) {
        for (auto& tunneler : mTunnelers) {
            tried++;
            Rectangle ancient_rectangle = pick_wall(tunneler);
            int feature_type = choose_feature(tunneler, ancient_rectangle);
            Rectangle* new_feature = create_possible_feature(feature_type, tunneler);
            bool is_free = (tunneler.direction % 2) ? verify_free(*new_feature, 1, 0) : verify_free(*new_feature, 0, 1);
            if (is_free) {
                tried = 0;
                push_feature(*new_feature);
                place_opening(tunneler);
                if (feature_type == ROOM) {
                    numberRooms++;
                    tunneler.mLastWasTunnel = 0;
                }
                else if (feature_type == TUNNEL) {
                    tunneler.mLastWasTunnel = 1;
                }
            }
            delete new_feature;
        }
    }
    place_stairway();

}


int **LevelGeneration::getMToGenerate() const
{
    return mToGenerate;
}


Rectangle& LevelGeneration::pick_wall(Tunnelers &tunneler)
{
    int id_rectangle = rand() % mRectangles.size();
    auto& rectangle_chosen = mRectangles[id_rectangle];
    int chosen_wall;
    if (((float)rand()/RAND_MAX) < tunneler.changeDirection) {
        chosen_wall = rand() % 4;
        tunneler.direction = chosen_wall;
    } else {
        chosen_wall = tunneler.direction;
    }
    switch (chosen_wall) {
        case DIR_RIGHT:
            tunneler.x = rectangle_chosen.x + rectangle_chosen.w - 1;
            tunneler.y = rand() % (rectangle_chosen.h - 2) + rectangle_chosen.y + 1;
            break;
        case DIR_LEFT:
            tunneler.x = rectangle_chosen.x;
            tunneler.y = rand() % (rectangle_chosen.h - 2) + rectangle_chosen.y + 1;
            break;
        case DIR_DOWN:
            tunneler.x = rand() % (rectangle_chosen.w - 2) + rectangle_chosen.x + 1;
            tunneler.y = rectangle_chosen.y + rectangle_chosen.h - 1;
            break;
        case DIR_UP:
            tunneler.x = rand() % (rectangle_chosen.w - 2) + rectangle_chosen.x + 1;
            tunneler.y = rectangle_chosen.y;
            break;
        default:
            break;
    }
    return rectangle_chosen;


}


int LevelGeneration::choose_feature(Tunnelers &tunneler, Rectangle& ancient_rectangle)
{
    bool is_room = ancient_rectangle.feature_type == ROOM;
    if (is_room) {
        return TUNNEL;
    } else {
        float possible = ((float)rand()/RAND_MAX);
        if (possible < tunneler.roomProba) {
            return ROOM;
        }
        else {
            return TUNNEL;
        }
    }
}


Rectangle* LevelGeneration::create_possible_feature(int type, Tunnelers &tunneler)
{
    Rectangle* new_feature = new Rectangle;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> random_tunnel(MIN_SIZE_TUNNEL, MAX_SIZE);
    std::uniform_int_distribution<int> random_room(MIN_SIZE_ROOM, MAX_SIZE);
    new_feature->feature_type = type;
    if (type == TUNNEL) {
        if (tunneler.direction % 2) {
            new_feature->w = tunneler.tunnelWidth;
            new_feature->h = random_tunnel(generator);
        }
        else {
            new_feature->h = tunneler.tunnelWidth;
            new_feature->w = random_tunnel(generator);
        }
    }
    else {
        new_feature->w = random_room(generator);
        new_feature->h = random_room(generator);
    }
    switch (tunneler.direction) {
        case DIR_RIGHT:
            new_feature->x = tunneler.x;
            new_feature->y = max(0, tunneler.y - new_feature->h / 2);
            break;
        case DIR_DOWN:
            new_feature->y = tunneler.y;
            new_feature->x = max(0, tunneler.x - new_feature->w / 2);
            break;
        case DIR_LEFT:
            new_feature->x = max(0, tunneler.x - new_feature->w + 1);
            new_feature->y = max(0, tunneler.y - new_feature->h / 2);
            break;
        case DIR_UP:
            new_feature->y = max(0, tunneler.y - new_feature->h + 1);
            new_feature->x = max(0, tunneler.x - new_feature->w / 2);
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
    // Coordinate for the 4 internals corner to put some torch
    int corner_x[2] = {x+1, x + w - 2};
    int corner_y[2] = {y+1, y + h - 2};
    for (int i = y+1; i < y+h - 1; ++i) {
        for (int j = x+1; j < x+w - 1 ; ++j) {
            mToGenerate[i][j] = FLOOR;
        }
    }
    // FOR DEBUG
    /*if (rectangle.feature_type == TUNNEL){
        for (int i = x; i < x+w; ++i) {
            mToGenerate[y][i] = WALL_TUNNEL;
            mToGenerate[y+h-1][i] = WALL_TUNNEL;
        }
        for (int i = y; i < y+h; ++i) {
            mToGenerate[i][x] = WALL_TUNNEL;
            mToGenerate[i][x+w-1] = WALL_TUNNEL;
        }
        return;
    }*/
    // Create WALLS
    for (int i = x; i < x+w; ++i) {
        mToGenerate[y][i] = WALL;
        mToGenerate[y+h-1][i] = WALL;
    }

    for (int i = y; i < y+h; ++i) {
        mToGenerate[i][x] = WALL;
        mToGenerate[i][x+w-1] = WALL;
    }
    // CREATE LIGHT IN CORNER
    if (((float)rand() / RAND_MAX) < PROBA_LIGHT) {
        int x_light = corner_x[rand()%2];
        int y_light = corner_y[rand()%2];
        mToGenerate[y_light][x_light] = FLOOR_LIGHT;
    }
    // CREATE MONSTERS
    int monsterNb = 0;
    while (monsterNb < mMaxMonsters) {
        if (((float)rand() / RAND_MAX) < mProbaMonster) {
            int y_random = rand() % (y + h - 2 - (y + 1)) + y + 1;
            int x_random = rand() % (x + w - 2 - (x + 1)) + x + 1;
            mToGenerate[y_random][x_random] = MONSTER;
        }
        monsterNb++;
    }
    // CREATE Objects
    int objectsNb = 0;
    while (objectsNb < mMaxObjects) {
        if (((float)rand() / RAND_MAX) < mProbaObjects) {
            int y_random = rand() % (y + h - 2 - (y + 1)) + y + 1;
            int x_random = rand() % (x + w - 2 - (x + 1)) + x + 1;
            if (mToGenerate[y_random][x_random] != FLOOR) {
                continue;
            }
            mToGenerate[y_random][x_random] = OBJECT;
        }
        objectsNb++;
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


void LevelGeneration::place_player(Transform *pTransform, int lvlnumber)
{
    int room_id = 0;
    while (mRectangles[room_id].feature_type != ROOM && mRectangles[room_id].feature_type != ROOM_STAIRWAY) {
        room_id++;
    }
    auto room = mRectangles[room_id];
    int x_random = rand() % (room.w - 2) + room.x + 1;
    int y_random = rand() % (room.h - 2) + room.y + 1;
    pTransform->x = x_random;
    pTransform->y = y_random;
    pTransform->levelMap = lvlnumber;
    if (lvlnumber != 0) {
        mToGenerate[y_random][x_random] = STAIRWAY_DOWN;
    }
}


void LevelGeneration::place_stairway()
{
    int random_room;
    int max_try = 100;
    int i = 0;
    do {
        i++;
        random_room = rand() % (mRectangles.size() - 1);
    } while (i < 100 && mRectangles[random_room].feature_type != ROOM);
    auto room = mRectangles[random_room];
    room.feature_type = ROOM_STAIRWAY;
    int x_random = rand() % (room.w - 2) + room.x + 1;
    int y_random = rand() % (room.h - 2) + room.y + 1;
    mToGenerate[y_random][x_random] = STAIRWAY_UP;
}
