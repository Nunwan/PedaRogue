//
// Created by nunwan on 23/07/2020.
//

#ifndef PEDAROGUE_MONSTERPARSE_HPP
#define PEDAROGUE_MONSTERPARSE_HPP

#include "nlohmann/json.hpp"
using json = nlohmann::json;

class MonsterParse
{
private:
    json mMainJson;
    json mRandomMonster;
    std::string mMonsterName;
    std::string mMonsterGlyph;
    int mMonsterColorR, mMonsterColorG, mMonsterColorB;
    std::unordered_map<std::string, int> mMonsterStat;
    int mMinLvl, mMaxLvl;
public:
    int getMMinLvl() const;

    int getMMaxLvl() const;

    int getMMonsterColorR() const;

    int getMMonsterColorG() const;

    int getMMonsterColorB() const;

    std::string &getMMonsterGlyph();

    MonsterParse();

    void singleRandomMonster();

    const std::unordered_map<std::string, int> &getMMonsterStat() const;

    std::string getName();

};


#endif //PEDAROGUE_MONSTERPARSE_HPP
