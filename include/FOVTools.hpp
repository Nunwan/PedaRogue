//
// Created by nunwan on 24/06/2020.
//

#ifndef PEDAROGUE_FOVTOOLS_HPP
#define PEDAROGUE_FOVTOOLS_HPP

#define DEBUG_MODE_FOV 0

#include <cmath>
#include <algorithm>
#include <vector>
#include "Components.hpp"
#include "Level.hpp"

void Line(std::vector<Transform> &pointLine, int x1, int y1, int x2, int y2);

void almost_circle(std::vector<Transform> &pointCircle, int x_or, int y_or, int x_max, int y_max, int range);
#endif //PEDAROGUE_FOVTOOLS_HPP
