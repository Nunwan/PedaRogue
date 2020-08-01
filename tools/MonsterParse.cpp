//
// Created by nunwan on 23/07/2020.
//

#include <fstream>
#include <iostream>
#include "include/MonsterParse.hpp"


MonsterParse::MonsterParse()
{
    std::ifstream ifjson("data/monsters.json");
    if (!ifjson)
    {
        std::cout << "cannot open monster json file \n It is possible that you're not in root project file" << std::endl;
        return;
    }
    mMainJson = nlohmann::json::parse(ifjson);
}


void MonsterParse::singleRandomMonster()
{
    // find a random monster
    int numero = rand() % mMainJson.size();
    auto iterate = mMainJson.begin();
    int i = 0;
    while (iterate != mMainJson.end() && i != numero) {
        iterate++;
        i++;
    }
    mRandomMonster = *iterate;
    // Parse stat
    auto stat = iterate->find("stats");
    mMonsterStat.clear();
    for (auto statLoop = stat->begin(); statLoop != stat->end(); statLoop++) {
        mMonsterStat.insert({statLoop.key(), statLoop.value()});
    }
    // Parse monster name
    mMonsterName = iterate.key();
    // Parse Glyph
    auto glyph = iterate->find("glyph");
    mMonsterGlyph = glyph.value();
    // Parse each colors
    auto color = iterate->find("color");
    mMonsterColorR = color.value()[0];
    mMonsterColorG = color.value()[1];
    mMonsterColorB = color.value()[2];
    // Parse min & max level
    auto lvl = iterate->find("spawn");
    auto lvlmin = lvl->find("lvlmin").value();
    auto lvlmax = lvl->find("lvlmax").value();
    mMinLvl = lvlmin;
    mMaxLvl = lvlmax;
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


int MonsterParse::getMMinLvl() const
{
    return mMinLvl;
}


int MonsterParse::getMMaxLvl() const
{
    return mMaxLvl;
}


