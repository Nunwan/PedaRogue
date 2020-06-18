//
// Created by nunwan on 17/06/2020.
//

#ifndef PEDAROGUE_LEVELGENERATION_HPP
#define PEDAROGUE_LEVELGENERATION_HPP

#include <vector>

#define MAX_DEPTH_TUNNEL 20
#define MAX_SIZE 25
#define MIN_SIZE 4
#define CHANGE_DIRECTION_PARENT 0.3
#define ROOM_PROBA_PARENT 0.4
#define TUNNEL_HALFWIDTH_PARENT 3
#define PROBA_DOOR 0.2
#define MAX_ROOMS 15

#define DIR_UP 3
#define DIR_LEFT 2
#define DIR_DOWN 1
#define DIR_RIGHT 0

#define EMPTY 0
#define FLOOR 1
#define WALL 2
#define WALL_TUNNEL 4
#define DOOR 3



struct Tunnelers {
    int x;
    int y;
    int direction;
    float changeDirection;
    float roomProba;
    // Half width bc tunnel will always has an odd width : enable no difficulty
    int tunnelHalfWidth;
    int mLastWasTunnel;
    int can_continue = 1;
};

/* For a Tunnel, x,y represent the middle left or up point of tunnel and w if the half width
 * For a Room, x,y represent the up left corner and h,w the height and width or the room
 */
struct Dimension {
    int x;
    int y;
    int h;
    int w;
};

class LevelGeneration {
private:
    std::vector<Tunnelers> mTunnelers;
    Dimension mLastRoom, mLastTunnel;
    int** mToGenerate;
    int mHeight;
    int mWidth;
    float mProbaDoor;
    int numberRooms;


    void CreateRectangularRoom(Dimension roomDimension);

    void place_opening(int tunneler_id);

    void CreateTunnel(Dimension dimension, int direction);

    // Rectangle is seen like a room : x,y is the topleft corner
    bool verify_free(Dimension rectangle);

    int PlaceRoom(int tunneler);
    int PlaceTunnel(int tunneler);

    void forward_until(int tunnerler);

public:
    int **getMToGenerate() const;

    LevelGeneration(int height_map, int width_map);

    virtual ~LevelGeneration();
    void run();

};



#endif //PEDAROGUE_LEVELGENERATION_HPP
