//
// Created by nunwan on 03/09/2020.
//


#include "UI_List.hpp"
#include "Window.hpp"
#define min(a,b) a<=b?a:b


Box::Box()
{
    h = HEIGHT_SCREEN - 1;
    w = 1 * WIDTH_SCREEN / 3 - 1;
    y = 0;
    x = 0;
}


Box::Box(int width, int height, int x_begin, int y_begin)
{
    w = width;
    h = height;
    x = x_begin;
    y = y_begin;
}


void Box::render(std::shared_ptr<Window> window)
{
    window->select_win(WIN_INFO);
    for (int x_it = x; x_it < x + w - 1; ++x_it) {
        window->print(x_it, y, "-", window->color_white);
        window->print(x_it, y + h - 1, "-", window->color_white);
    }
    for (int y_it = y; y_it < y + h - 1; ++y_it) {
        window->print(x, y_it, "|", window->color_white);
        window->print(x + w - 1, y_it, "|", window->color_white);
    }
}


void UI_List::render(std::shared_ptr<Window> window)
{
    Box::render(window);
    int y_it = y + 2;
    for (auto& item : mItems) {
        item.render(window, 1, y_it, 1 * WIDTH_SCREEN / 3 - 5);
        y_it++;
    }

}


void UI_List::createList(std::unordered_map<std::string, int> list)
{
    if (mItems.size()) {
        mItems.clear();
    }
    for (auto const& pair : list) {
        mItems.push_back(Item(pair.first, pair.second));
    }
}


void UI_List::clear_item(std::shared_ptr<Window> window, int y)
{
    window->clear_line(y, 1, 1 * WIDTH_SCREEN / 3 - 1);


}


Item::Item(Color default_color, Color selected_color)
{
    mDefaultColor = default_color;
    mSelectedColor = selected_color;
    mColor = &mDefaultColor;
}


void Item::render(std::shared_ptr<Window> window, int x, int y, int x_max)
{
    window->select_win(WIN_INFO);
    std::string label_truncate = mLabel.substr(0, min(x_max, mLabel.length()));
    char* labelc = &label_truncate[0];
    window->clear_line(y, 1, 1 * WIDTH_SCREEN / 3 - 1);
    window->print(x, y, labelc, color_from_argb(0xff, mColor->r, mColor->g, mColor->b));
    auto number_string = std::to_string(mNumber);
    char* number_char = &number_string[0];
    window->print(1 * WIDTH_SCREEN / 3 - 4, y, number_char, color_from_argb(0xff, mColor->r, mColor->g, mColor->b));
    window->refresh();
}


void Item::selected()
{
    mColor = &mSelectedColor;

}


void Item::unselected()
{
    mColor = &mDefaultColor;
}


Item::Item(std::string label, int number, Color default_color, Color selected_color)
{
    Item(default_color, selected_color);
    mLabel = label;
    mNumber = number;
}
