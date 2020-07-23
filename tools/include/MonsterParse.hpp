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

public:
    MonsterParse();

    void singleRandomMonster();

    int getStat(std::string statname);

    std::string getName();



};


#endif //PEDAROGUE_MONSTERPARSE_HPP
