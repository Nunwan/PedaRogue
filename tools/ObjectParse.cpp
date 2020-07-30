//
// Created by nunwan on 23/07/2020.
//

#include <fstream>
#include <iostream>
#include "include/ObjectParse.hpp"


ObjectParse::ObjectParse()
{
    std::ifstream ifjson("data/objects.json");
    if (!ifjson)
    {
        std::cout << "cannot open object json file \n It is possible that you're not in root project file" << std::endl;
        return;
    }
    mMainJson = nlohmann::json::parse(ifjson);
}


void ObjectParse::singleRandomObject()
{
    int numero = rand() % mMainJson.size();
    auto iterate = mMainJson.begin();
    int i = 0;
    while (iterate != mMainJson.end() && i != numero) {
        iterate++;
        i++;
    }
    mRandomObject = *iterate;
    auto stat = iterate->find("stats");
    mObjectStat.clear();
    for (auto statLoop = stat->begin(); statLoop != stat->end(); statLoop++) {
        mObjectStat.insert({statLoop.key(), statLoop.value()});
    }
    mObjectName = iterate.key();
    auto glyph = iterate->find("glyph");
    mObjectGlyph = glyph.value();
    auto color = iterate->find("color");
    mObjectColorR = color.value()[0];
    mObjectColorG = color.value()[1];
    mObjectColorB = color.value()[2];
}


std::string ObjectParse::getName()
{
    return mObjectName;
}


const std::unordered_map<std::string, int> &ObjectParse::getMObjectStat() const
{
    return mObjectStat;
}


std::string &ObjectParse::getMObjectGlyph()
{
    return mObjectGlyph;
}


int ObjectParse::getMObjectColorR() const
{
    return mObjectColorR;
}


int ObjectParse::getMObjectColorG() const
{
    return mObjectColorG;
}


int ObjectParse::getMObjectColorB() const
{
    return mObjectColorB;
}


const std::string &ObjectParse::getMObjectName() const
{
    return mObjectName;
}


