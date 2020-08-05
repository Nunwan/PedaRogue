//
// Created by nunwan on 23/07/2020.
//

#ifndef PEDAROGUE_OBJECTPARSE_HPP
#define PEDAROGUE_OBJECTPARSE_HPP

#include "nlohmann/json.hpp"
using json = nlohmann::json;

class ObjectParse
{
private:
    json mMainJson;
    json mRandomObject;
    std::string mObjectName;
    std::string mObjectGlyph;
    int mObjectColorR, mObjectColorG, mObjectColorB;
    std::unordered_map<std::string, int> mObjectStat;
    int mMinLvl, mMaxLvl;
public:
    int getMMinLvl() const;

    int getMMaxLvl() const;

public:
    const std::string &getMObjectName() const;
    int getMObjectColorR() const;

    int getMObjectColorG() const;

    int getMObjectColorB() const;

    std::string &getMObjectGlyph();

    ObjectParse();

    void singleRandomObject();

    const std::unordered_map<std::string, int> &getMObjectStat() const;

    std::string getName();

};


#endif //PEDAROGUE_OBJECTPARSE_HPP
