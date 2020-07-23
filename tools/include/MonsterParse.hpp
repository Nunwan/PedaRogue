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

public:
    MonsterParse();

    void singleRandomMonster();



};


#endif //PEDAROGUE_MONSTERPARSE_HPP
