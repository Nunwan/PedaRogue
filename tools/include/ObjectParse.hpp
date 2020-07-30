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
public:
    const std::string &getMObjectName() const;

private:
    std::string mObjectGlyph;
    int mObjectColorR, mObjectColorG, mObjectColorB;
public:
    int getMObjectColorR() const;

    int getMObjectColorG() const;

    int getMObjectColorB() const;

public:
    std::string &getMObjectGlyph();

private:
    std::unordered_map<std::string, int> mObjectStat;

public:
    ObjectParse();

    void singleRandomObject();

    const std::unordered_map<std::string, int> &getMObjectStat() const;

    std::string getName();
};


#endif //PEDAROGUE_OBJECTPARSE_HPP
