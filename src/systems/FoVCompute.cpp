//
// Created by nunwan on 24/06/2020.
//

#include <iostream>
#include "systems/FoVCompute.hpp"
#include "Engine.hpp"


class Comparaison_Distance {
private:
    int x_origin;
    int y_origin;
public:
    Comparaison_Distance(int x, int y){x_origin =x; y_origin = y;}
    bool operator() (Transform t1, Transform t2) const {
        return inf_by(t1, t2, x_origin, y_origin);
    }
};

void FoVCompute::compute()
{
    for (auto const& player : mEntities) {
        auto& playerPos = mEngine->GetComponent<Transform>(player);
        auto level = mEngine->GetLevel(playerPos.levelMap);
        auto& playerStat = mEngine->GetComponent<Stats>(player);
        ComputeFoV(playerPos.x, playerPos.y, playerStat.visibility, playerPos.levelMap);
    }
}


void FoVCompute::ComputeFoV(int x, int y, int range, int levelnumber)
{

#if DEBUG_MODE_FOV == 1
    for (int i = 0; i < HEIGHT_MAP; ++i) {
        for (int j = 0; j < WIDTH_MAP; ++j) {
            auto& entity = mMap[i][j];
            if (mEngine->HasComponent<Render>(entity)) {
                auto& entityRender = mEngine->GetComponent<Render>(entity);
                entityRender.color = mEngine->getMWindow()->color_white;
            }
        }

    }
#endif
    std::vector<Transform> pointCircle;
    std::vector<Transform> pointLine;
    almost_circle(pointCircle, x, y, WIDTH_MAP, HEIGHT_MAP, range);

    for (auto const& point : pointCircle) {
        pointLine.clear();
        Line(pointLine, x, y, point.x, point.y);
        // print_vec(pointLine);
        std::sort(pointLine.begin(), pointLine.end(), Comparaison_Distance(x, y));
        // print_vec(pointLine);
        del_after_block(pointLine, levelnumber);
        for (auto const& point : pointLine) {
            to_display(point.x, point.y, levelnumber);
        }
    }
#if DEBUG_MODE_FOV == 1
    for (auto const& point : pointCircle) {
        auto& entity = mMap[point.y][point.x];
        if (mEngine->HasComponent<Render>(entity)) {
            auto& entityRender = mEngine->GetComponent<Render>(entity);
            entityRender.color = mEngine->getMWindow()->color_red;
        }
    }
#endif
}



int FoVCompute::to_display(int x, int y, int levelnumber)
{
    auto map = mEngine->GetLevel(levelnumber)->getMMap();
    Entity entity = map[y][x];
    if (mEngine->HasComponent<Render>(entity)) {
        auto &entityRender = mEngine->GetComponent<Render>(entity);
#if DEBUG_MODE_FOV == 1
        entityRender.color = mEngine->getMWindow()->color_blue;
#endif
        entityRender.to_display = true;
    }
    if (mEngine->HasComponent<RigidBody>(entity)) {
        auto& entityRigid = mEngine->GetComponent<RigidBody>(entity);
        return !entityRigid.transparent;
    }
    return false;
}


void FoVCompute::del_after_block(vector<Transform> &pointLine, int levelnumber)
{
    int i = 0;
    while (i < pointLine.size()) {
        auto point = pointLine[i];
        auto map = mEngine->GetLevel(levelnumber)->getMMap();
        Entity entity = map[point.y][point.x];
        if (mEngine->HasComponent<RigidBody>(entity)) {
            auto& entityRigid = mEngine->GetComponent<RigidBody>(entity);
            if (!entityRigid.transparent) {
                break;
            }
        }
        i++;
    }
    if (i < pointLine.size()) {
        pointLine.resize(i+1);
    }
}


bool inf_by(Transform t1, Transform t2, int x_or, int y_or)
{
    float distance1 = std::sqrt((x_or - t1.x)*(x_or - t1.x) + (y_or - t1.y)*(y_or - t1.y));
    float distance2 = std::sqrt((x_or - t2.x)*(x_or - t2.x) + (y_or - t2.y)*(y_or - t2.y));
    return distance1 <= distance2;
}


