//
// Created by nunwan on 03/09/2020.
//

#ifndef PEDAROGUE_UI_LIST_HPP
#define PEDAROGUE_UI_LIST_HPP

#include <memory>
#include <Window.hpp>

class Box {
    int h, w, x, y;
public:
    Box();
    Box(int width, int height, int x_begin, int y_begin);

    virtual void render(std::shared_ptr<Window> window);
};

class UI_List : public Box
{
public:
    void render(std::shared_ptr<Window> window) override;
};

class Item;





#endif //PEDAROGUE_UI_LIST_HPP
