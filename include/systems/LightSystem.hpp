//
// Created by nunwan on 25/06/2020.
//

#ifndef PEDAROGUE_LIGHTSYSTEM_HPP
#define PEDAROGUE_LIGHTSYSTEM_HPP

#include "FoVCompute.hpp"

class LightSystem : public FoVCompute
{
public:
    /**
     * @brief           Update the displayed map with the light
     *                  Lights have the same behavior as a player for their FOV and computing fov for them is
     *                  quite the same. The major difference is that a light and its area can be seen only if the
     *                  player can be seen by the light
     */
    void update() override;
private:
    /**
     * @brief                   Return if there is a non transparent block in the line
     * @param pointLine         The line of point which will be displayed
     * @param levelnumber       The level number of this line
     * @return                  1 if there are a non transparent block 0 if not
     */
    bool nottransparent_between(vector<Transform> &pointLine, int levelnumber);
};


#endif //PEDAROGUE_LIGHTSYSTEM_HPP
