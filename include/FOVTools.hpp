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

/**
 * @brief               Add points which are bresenham'line points between the two points 1, 2
 * @param pointLine     The vector to fill with the good points
 * @param x1            x coordinate of the first point
 * @param y1            y coordinate of the first point
 * @param x2            x coordinate of the second point
 * @param y2            y coordinate of the second point
 */
void Line(std::vector<Transform> &pointLine, int x1, int y1, int x2, int y2);

/**
 * @brief                   Fill vector with point of a circle of origin x_or,y_or and radius range while point
 *                          has coordinates of maximum x_max, y_max
 * @param pointCircle       vector to fill with the circle
 * @param x_or              x coordinate of the center point
 * @param y_or              y coordinate of the center point
 * @param x_max             maximum of the coordinate x to consider
 * @param y_max             maximum of the coordinate y to consider
 * @param range             radius of the pseudo circle
 */
void almost_circle(std::vector<Transform> &pointCircle, int x_or, int y_or, int x_max, int y_max, int range);
#endif //PEDAROGUE_FOVTOOLS_HPP
