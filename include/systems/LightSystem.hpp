//
// Created by nunwan on 25/06/2020.
//

#ifndef PEDAROGUE_LIGHTSYSTEM_HPP
#define PEDAROGUE_LIGHTSYSTEM_HPP

#include "FoVCompute.hpp"

class LightSystem : public FoVCompute
{
public:
    void compute() override;
private:
    bool nottransparent_between(vector<Transform> &pointLine, int levelnumber);
};


#endif //PEDAROGUE_LIGHTSYSTEM_HPP
