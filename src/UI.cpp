//
// Created by nunwan on 02/09/2020.
//


#include <memory>
#include <Window.hpp>
#include "UI.hpp"

UI::UI(std::shared_ptr<Window> win) : UI()
{
    mWindow = win;
    mInventory = UI_List();
    mToRenderBox.clear();
}

void UI::push_message(Message message)
{
    mWindow->select_win(WIN_MSG);
    auto color_message = color_from_argb(0xff, message.r, message.g, message.b);
    if (to_clear || currentMessage.length() > 2 * WIDTH_SCREEN / 3) {
        mWindow->clear();
        currentMessage.clear();
        to_clear = false;
    }
    currentMessage = currentMessage + " " + message.text;
    char* cstr = &currentMessage[0];
    mWindow->print(0, 0, cstr, color_message);
    mWindow->refresh();
}


void UI::render_status_bar(Stats playerStat)
{
    mWindow->select_win(WIN_STATUS);
    mWindow->clear();
    std::string pv = std::to_string(playerStat.stats["pv"]);
    char* pv_c = &pv[0];
    int r_pv(0xff), g_pv(0xff), b_pv(0xff);
    if (playerStat.stats["pv"] < 10) {
        g_pv = 0;
        b_pv = 0;
    }
    std::string mana = std::to_string(playerStat.stats["mana"]);
    char* mana_c = &mana[0];
    int r_mana(0xff), g_mana(0xff), b_mana(0xff);
    if (playerStat.stats["mana"] < 10) {
        g_mana = 0;
        b_mana = 0;
    }
    mWindow->print(0, 0, "PV : ", mWindow->color_white);
    mWindow->print(6, 0, pv_c, color_from_argb(0xff, r_pv, g_pv, b_pv));
    mWindow->print(11, 0, "Mana : ", mWindow->color_white);
    mWindow->print(18, 0, mana_c, color_from_argb(0xff, r_mana, g_mana, b_mana));
    mWindow->refresh();
}


void UI::newTurn()
{
    to_clear = true;
}


bool UI::process_key(EventWin event)
{
    if (event.key == TK_ESCAPE) {
        clear();
        mToRenderBox.clear();
        return true;
    }
    auto command = mUIBindings[event.key];
    switch (command) {
        case OpenInventory: {
            mToRenderBox.push_back(&mInventory);
        }
    }
    return false;



}


UI::UI()
{
    mUIBindings.insert({TK_I, OpenInventory});
    mUIBindings.insert({TK_UP, UpMenu});
    mUIBindings.insert({TK_DOWN, DownMenu});

}


void UI::render()
{
    if (mToRenderBox.size()) {
        for (auto box : mToRenderBox) {
            box->render(mWindow);
        }

    }
}


void UI::clear()
{
    mWindow->select_win(WIN_INFO);
    mWindow->clear();
}



