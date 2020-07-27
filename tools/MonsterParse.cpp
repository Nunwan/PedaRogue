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
        i++;
    }
    mRandomMonster = *iterate;
    auto stat = iterate->find("stats");
    mMonsterStat.clear();
    for (auto statLoop = stat->begin(); statLoop != stat->end(); statLoop++) {
        mMonsterStat.insert({statLoop.key(), statLoop.value()});
    }
    mMonsterName = iterate.key();
    auto glyph = iterate->find("glyph");
    mMonsterGlyph = glyph.value();

    auto r = iterate->find("r");
    auto g = iterate->find("g");
    auto b = iterate->find("b");
    mMonsterColorR = r.value();
    mMonsterColorG = g.value();
    mMonsterColorB = b.value();
}


std::string MonsterParse::getName()
{
    return mMonsterName;
}


const std::unordered_map<std::string, int> &MonsterParse::getMMonsterStat() const
{
    return mMonsterStat;
}


std::string &MonsterParse::getMMonsterGlyph()
{
    return mMonsterGlyph;
}


int MonsterParse::getMMonsterColorR() const
{
    return mMonsterColorR;
}


int MonsterParse::getMMonsterColorG() const
{
    return mMonsterColorG;
}


int MonsterParse::getMMonsterColorB() const
{
    return mMonsterColorB;
}


