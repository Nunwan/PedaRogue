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
#define PROBA_LIGHT 0.5f

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
#define FLOOR_LIGHT 5
#define MONSTER 7

#define LOG_MAP 0


struct Tunnelers {
    int x;
    int y;
    int direction;
    float changeDirection;
    float roomProba;
    // Half width bc tunnel will always has an odd width : enable no difficulty
    int tunnelWidth;
    float probaLight;
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
    // The future map but with integers and not entities
    int** mToGenerate;
    // Size of the map
    int mHeight;
    int mWidth;
    // Probability of set a door in an opening
    float mProbaDoor;
    float mProbaMonster;
    float mProbaObjects;
    int mMaxMonsters;


    /**
     * @brief               Place at the position of the tunneler an opening : can be a floor or a door
     * @param tunneler      the tunneler who wants a new opening
     */
    void place_opening(Tunnelers &tunneler);


    // Rectangle is seen like a room : x,y is the topleft corner
    /**
     * @brief               Take a rectangle and an offset and check if a room with offset margins can fit in the
     *                      current map generation
     * @param rectangle     New rectangle to generate
     * @param offset_x      Margin each x side of the room
     * @param offset_y      Margin each y side of the room
     * @return              1 if it is possible to create the rectangle 0 if not
     */
    bool verify_free(Rectangle rectangle, int offset_x = 0, int offset_y = 0);


public:
    // Getters
    int **getMToGenerate() const;

    LevelGeneration(int height_map, int width_map, float probaMonster, float probaObject,
                    int maxMonster);

    virtual ~LevelGeneration();

    /**
     * @brief   Main generation function.
     *          Create a map thanks to tunnelers and save it in mToGenerate
     */
    void run();

    /**
     * @brief               Choose randomly a wall in all the possible walls of the current state of generation
     * @param tunneler     The tunneler who want to create a new feature
     * @return              The rectangle of the feature where the wall is
     */
    Rectangle& pick_wall(Tunnelers &tunneler);

    /**
     * @brief                       Choose a feature between those which are possible
     * @param tunneler             tunneler who want to create a new feature
     * @param ancient_rectangle     The rectangle where the tunneler begin the construction
     * @return                      The type (int) of the feature to create
     */
    static int choose_feature(Tunnelers &tunneler, Rectangle& ancient_rectangle);

    /**
     * @brief               Create a randomly feature of the good type and return it
     * @param type          Type of the feature to create
     * @param tunneler     the tunneler who want to create this feature
     * @return
     */
    Rectangle* create_possible_feature(int type, Tunnelers &tunneler);

    /**
     * @brief               With the consideration that the feature can be create (verify_free), push the feature
     *                      to mToGenerate
     * @param rectangle     Rectangle to create
     */
    void push_feature(Rectangle rectangle);

    /**
     * @brief               Place a player in the map, randomly
     * @param pTransform    The transform of the player
     */
    void place_player(Transform *pTransform);

    // Log functions
    void write_log_map();
};



#endif //PEDAROGUE_LEVELGENERATION_HPP
