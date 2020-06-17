//
// Created by nunwan on 17/06/2020.
//

#ifndef PEDAROGUE_LEVELGENERATION_HPP
#define PEDAROGUE_LEVELGENERATION_HPP

#include <vector>

#define MAX_DEPTH_TUNNEL 20
#define CHANGE_DIRECTION_PARENT 0.3
#define ROOM_PROBA_PARENT 0.4
#define TUNNEL_WIDTH_PARENT 3
#define PROBA_DOOR 0.2
#define DIR_DOWN 1
#define DIR_RIGHT 0

#define EMPTY 0
#define FLOOR 1
#define WALL 2
#define DOOR 3



struct Tunnelers {
    int x;
    int y;
    int direction;
    float changeDirection;
    float roomProba;
    int tunnelWidth;
};

class LevelGeneration {
private:
    std::vector<Tunnelers> mTunnelers;
    int** mToGenerate;
    int mHeight;
    int mWidth;
    float mProbaDoor;
public:
    LevelGeneration(int height_map, int width_map);

    virtual ~LevelGeneration();

    void CreateRectangularRoom(int x, int y, int w, int h);

    void place_opening(int x, int y);
};



#endif //PEDAROGUE_LEVELGENERATION_HPP
