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
    window->clear_area(x, y, w, h);
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
    int x_middle = (1 * WIDTH_SCREEN/ 3 - 2 )/ 2 - (mTitle.length() / 2);
    char* titlec = &mTitle[0];
    window->print(x_middle, y + 1, titlec, window->color_white);
    int y_it = y + 2;
    int i = 0;
    for (auto& item : mItems) {
        if (i == mCurrentSelected) {
            window->print(x + 1, y_it, "> ", window->color_blue);
            item.render(window, x + 3, y_it, x + w - 4);

        } else {
            item.render(window, x + 1, y_it, x + w - 2);
        }
        y_it++;
        i++;
    }

}


void UI_List::createList(const std::unordered_map<std::string, int>& list)
{
    if (mItems.size()) {
        mItems.clear();
    }
    for (auto const& pair : list) {
        mItems.emplace_back(pair.first, pair.second);
    }
    mCurrentSelected = 0;
    if (mItems.size()) {
        mItems[mCurrentSelected].selected();
    }
}


void UI_List::clear_item(std::shared_ptr<Window> window, int y)
{
    window->clear_line(y, 1, 1 * WIDTH_SCREEN / 3 - 1);
}


void UI_List::select_item(int offset)
{
    if (mCurrentSelected + offset >= 0 && mCurrentSelected + offset < mItems.size()) {
        mItems[mCurrentSelected].unselected();
        mCurrentSelected += offset;
        mItems[mCurrentSelected].selected();
    }
}


void UI_List::select_next()
{
    select_item(1);
}


void UI_List::select_previous()
{
    select_item(-1);
}


UI_List::UI_List(const std::string &mTitle, bool permanent) : mTitle(mTitle), mPermanent(permanent)
{}


Command * UI_List::choose()
{
    return mItems[mCurrentSelected].choosen();
}


void UI_List::push_item(std::string label, int number, Command* command)
{
    mItems.emplace_back(label, number, command);
    if (mItems.size() == 1) {
        mCurrentSelected = 0;
        mItems.back().selected();
    }

}


void UI_List::clear_items()
{
    mItems.clear();
}


bool UI_List::isMPermanent() const
{
    return mPermanent;
}


Item::Item(Color default_color, Color selected_color)
{
    mDefaultColor = default_color;
    mSelectedColor = selected_color;
    mColor = &mDefaultColor;
}


void Item::render(std::shared_ptr<Window> window, int x, int y, int x_max)
{
    // mColor = &mDefaultColor;
    window->select_win(WIN_INFO);
    std::string label_truncate = mLabel.substr(0, min(x_max, mLabel.length()));
    char* labelc = &label_truncate[0];
    window->clear_line(y, 1, 1 * WIDTH_SCREEN / 3 - 1);
    window->print(x, y, labelc, color_from_argb(0xff, mColor->r, mColor->g, mColor->b));
    if (mNumber>=0) {
        auto number_string = std::to_string(mNumber);
        char *number_char = &number_string[0];
        window->print(1 * WIDTH_SCREEN / 3 - 4, y, number_char, color_from_argb(0xff, mColor->r, mColor->g, mColor->b));
    }
}


void Item::selected()
{
    mColor = &mSelectedColor;

}


void Item::unselected()
{
    mColor = &mDefaultColor;
}


Item::Item(std::string label, int number, Command* command, Color default_color, Color selected_color)
{
    mDefaultColor = default_color;
    mSelectedColor = selected_color;
    mColor = &mDefaultColor;
    mLabel = label;
    mNumber = number;
    mCommand = command;
}


Command * Item::choosen()
{
    return mCommand;
}


Item::~Item()
{
    delete mCommand;

}
