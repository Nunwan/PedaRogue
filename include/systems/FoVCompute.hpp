//
// Created by nunwan on 24/06/2020.
//

#ifndef PEDAROGUE_FOVCOMPUTE_HPP
#define PEDAROGUE_FOVCOMPUTE_HPP


#include <core/ECSTypes.hpp>
#include "FOVTools.hpp"


class FoVCompute : public System
{
public:
    void compute();
    void ComputeFoV(int x, int y);
};


#endif //PEDAROGUE_FOVCOMPUTE_HPP
