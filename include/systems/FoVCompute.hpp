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
    virtual void compute();
    void ComputeFoV(int x, int y, int range, int levelnumber);
    int to_display(Entity entity);
    Entity monster_on_point(int x, int y, int levelnumber);
    Entity object_on_point(int x, int y, int levelnumber);

    void del_after_block(vector<Transform> &vector, int levelnumber);
};


#endif //PEDAROGUE_FOVCOMPUTE_HPP
