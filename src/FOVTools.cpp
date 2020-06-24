//
// Created by nunwan on 24/06/2020.
//

#include "FOVTools.hpp"

#define max(a,b) a<=b?b:a



void Line(std::vector<Transform> &pointLine, int x1, int y1, int x2, int y2)
{
    const bool steep = abs(y2 - y1) > abs(x2 - x1);
    if (steep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    const int dx = x2 - x1;
    const int dy = abs(y2 - y1);

    float error = (float)dx / 2.0f;
    const int ystep = (y1 < y2)? 1 : -1;
    int y = y1;

    const int maxX = x2;
    int stop = 0;
    for (int x = x1; x <= maxX; x++) {
        if (steep) {
            Transform newPoint = {y ,x, -1};
            pointLine.push_back(newPoint);
        }
        else {
            Transform newPoint = {x, y, -1};
            pointLine.push_back(newPoint);
        }
        error -= (float)dy;
        if (error < 0) {
            y += ystep;
            error += (float)dx;
        }
        if (stop && false) {  // Remove false
            break;
        }
    }
}


void almost_circle(std::vector<Transform>& pointCircle, int x_or, int y_or, int max_x, int max_y, int range)
{
    float maxRange = range / 1.01;
    float minRange = range / 1.41;
    if (x_or - range < 0) {
        for (int y = max(0, y_or - range); y < y_or + range; ++y) {
            Transform newPoint = {0, y, -1};
            pointCircle.push_back(newPoint);
        }
    }
    if (y_or - range < 0) {
        for (int x = max(0, x_or - range); x < x_or + range; ++x) {
            Transform newPoint = {x, 0, -1};
            pointCircle.push_back(newPoint);
        }
    }
    for (int x = 0; x < max_x; ++x) {
        for (int y = 0; y < max_y; ++y) {
            float distance = std::sqrt((x_or - x)*(x_or - x) + (y_or - y)*(y_or - y));
            if (minRange < distance  && distance < maxRange) {

                Transform newPoint = {x, y, -1};
                pointCircle.push_back(newPoint);
            }
        }
    }
}
