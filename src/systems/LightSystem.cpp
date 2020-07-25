//
// Created by nunwan on 25/06/2020.
//

#include "systems/LightSystem.hpp"
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


bool LightSystem::nottransparent_between(vector<Transform> &pointLine, int levelnumber)
{
    int i = 0;
    while (i < pointLine.size()) {
        auto point = pointLine[i];
        auto map = mEngine->GetLevel(levelnumber)->getMMap();
        Entity entity = map[point.y][point.x];
        if (mEngine->HasComponent<RigidBody>(entity)) {
            auto& entityRigid = mEngine->GetComponent<RigidBody>(entity);
            if (!entityRigid.transparent) {
                return true;
            }
        }
        i++;
    }
    return false;
}
void LightSystem::compute()
{
    auto& player = mEngine->GetPlayer();
    auto& playerPos = mEngine->GetComponent<Transform>(player);
    std::vector<Transform> pointLine;
    for (auto const& light : mEntities) {
        auto& lightPos = mEngine->GetComponent<Transform>(light);
        pointLine.clear();
        Line(pointLine, lightPos.x, lightPos.y, playerPos.x, playerPos.y);
        std::sort(pointLine.begin(), pointLine.end(), Comparaison_Distance(lightPos.x, lightPos.y));
        if (!nottransparent_between(pointLine, lightPos.levelMap)) {
            auto level = mEngine->GetLevel(lightPos.levelMap);
            auto &lightStat = mEngine->GetComponent<Stats>(light);
            ComputeFoV(lightPos.x, lightPos.y, lightStat.stats["visibility"], lightPos.levelMap);
        }
    };
}
