//
// Created by nunwan on 24/06/2020.
//

#ifndef PEDAROGUE_FOVCOMPUTE_HPP
#define PEDAROGUE_FOVCOMPUTE_HPP


#include <core/ECSTypes.hpp>
#include "FOVTools.hpp"

bool inf_by(Transform t1, Transform t2, int x_or, int y_or);
class Comparaison_Distance;

class FoVCompute : public System
{
public:

    /**
     * @brief       Update the FOV of the game in order to see what player has to see
     */
    virtual void update();

    /**
     * @brief                   Main function of the calculus behind the FOV
     * @param x                 The x coordinate of the origin of the fov
     * @param y                 The y coordinate of the origin of the fov
     * @param range             The range of the Fov (almost circular)
     * @param levelnumber       The number for the level to calculate fov
     */
    void ComputeFoV(int x, int y, int range, int levelnumber);

    /**
     * @brief               Display an entity at screen
     * @param entity        The entity to display
     * @return              A boolean : "the entity is not transparent"
     */
    int to_display(Entity entity);

    /**
     * @brief                   Return a monster on the point x,y at the level levelnumber
     * @param x                 The x coordinate for the monster to be find
     * @param y                 The y coordinate for the monster to be find
     * @param levelnumber       The level in which the monster can be
     * @return                  The entity monster at thoses coordinates
     */
    Entity monster_on_point(int x, int y, int levelnumber);

    /**
     * @brief                   Return a object on the point x,y at the level levelnumber
     * @param x                 The x coordinate for the object to be find
     * @param y                 The y coordinate for the object to be find
     * @param levelnumber       The level in which the object can be
     * @return                  The entity object at thoses coordinates
     */
    Entity object_on_point(int x, int y, int levelnumber);


    /**
     * @brief                   Reduce the entities to display if there is a not transparent block in the line
     * @param line              The line of entities originally displayed
     * @param levelnumber       The level which gonna be display
     */
    void del_after_block(std::vector<Transform> &line, int levelnumber);
};


#endif //PEDAROGUE_FOVCOMPUTE_HPP
