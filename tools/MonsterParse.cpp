//
// Created by nunwan on 23/07/2020.
//

#include <fstream>
#include "include/MonsterParse.hpp"


MonsterParse::MonsterParse()
{
    std::ifstream ifjson("data/monsters.json");
    ifjson >> mMainJson;
}


void MonsterParse::singleRandomMonster()
{
    int numero = rand() % mMainJson.size();
    auto iterate = mMainJson.rbegin();
    int i = 0;
    while (iterate != mMainJson.rend() && i != numero) {
        iterate++;
    }
    mRandomMonster = *iterate;
}
