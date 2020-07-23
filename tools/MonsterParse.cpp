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
    auto iterate = mMainJson.begin();
    int i = 0;
    while (iterate != mMainJson.end() && i != numero) {
        iterate++;
    }
    mRandomMonster = *iterate;
    mMonsterName = iterate.key();
}


int MonsterParse::getStat(std::string statname)
{
    auto stat = mRandomMonster.find("stats")->find(statname);
    return stat.value();
}


std::string MonsterParse::getName()
{
    return mMonsterName;
}

