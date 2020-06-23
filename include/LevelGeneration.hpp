//
// Created by nunwan on 17/06/2020.
//

#ifndef PEDAROGUE_LEVELGENERATION_HPP
#define PEDAROGUE_LEVELGENERATION_HPP

#include <vector>
#include "Components.hpp"

#define MAX_DEPTH_TUNNEL 20
#define MAX_SIZE 15
#define MIN_SIZE_ROOM 8
#define MIN_SIZE_TUNNEL 6
#define CHANGE_DIRECTION_PARENT 0.5
#define ROOM_PROBA_PARENT 0.8f
#define TUNNEL_HALFWIDTH_PARENT 4
#define PROBA_DOOR 0.2
#define MAX_ROOMS 15
#define MIN_ROOM 8

#define ROOM 0
#define TUNNEL 1

#define DIR_UP 3
#define DIR_LEFT 2
#define DIR_DOWN 1
#define DIR_RIGHT 0

#define EMPTY 0
#define FLOOR 1
#define WALL 2
#define WALL_TUNNEL 4
#define DOOR 3

#define LOG_MAP 0


struct Tunnelers {
    int x;
    int y;
    int direction;
    float changeDirection;
    float roomProba;
    // Half width bc tunnel will always has an odd width : enable no difficulty
    int tunnelWidth;
    int mLastWasTunnel;
    int can_continue = 1;
};

/* For a Tunnel, x,y represent the middle left or up point of tunnel and w if the half width
 * For a Rectangle, x,y represent the up left corner and h,w the height and width or the room
 */
struct Rectangle {
    int x;
    int y;
    int h;
    int w;
    int feature_type;
};

class LevelGeneration {
private:
    std::vector<Tunnelers> mTunnelers;
    std::vector<Rectangle> mRectangles;
    Rectangle mLastRoom, mLastTunnel;
    int** mToGenerate;
    int mHeight;
    int mWidth;
    float mProbaDoor;


    void CreateRectangularRoom(Rectangle roomDimension);

    void place_opening(Tunnelers &tunneler);

    void CreateTunnel(Rectangle dimension, int direction);

    // Rectangle is seen like a room : x,y is the topleft corner
    bool verify_free(Rectangle rectangle, int offset_x = 0, int offset_y = 0);

    int PlaceRoom(int tunneler);
    int PlaceTunnel(int tunneler);

    void forward_until(int tunnerler, int limite = -1);

public:
    int **getMToGenerate() const;

    LevelGeneration(int height_map, int width_map);

    virtual ~LevelGeneration();
    void run();

    Rectangle& pick_wall(Tunnelers &tunnelers);

    static int choose_feature(Tunnelers &tunnelers, Rectangle& ancient_rectangle);

    Rectangle* create_possible_feature(int type, Tunnelers &tunnelers);

    void push_feature(Rectangle rectangle);

    void write_log_map();

    void place_player(Transform *pTransform);
};



#endif //PEDAROGUE_LEVELGENERATION_HPP
