//
// Created by nunwan on 02/09/2020.
//


#include <memory>
#include <Window.hpp>
#include "UI.hpp"
#include "Engine.hpp"

UI::UI(std::shared_ptr<Window> win)
{
    mWindow = win;
    mToRenderBox.clear();
    to_clear = false;
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





void UI::render()
{
    mWindow->select_win(WIN_INFO);
    mWindow->clear();
    if (mToRenderBox.size()) {
        for (auto box : mToRenderBox) {
            box->render(mWindow);
        }
    }
    mWindow->refresh();
}


void UI::clear_last()
{
    if (!isEmpty()) {
        auto back = mToRenderBox.back();
        mToRenderBox.pop_back();
        if (!back->isMPermanent())
        {
            UI_List* list = dynamic_cast<UI_List *>(back);
            list->clear_items();
            delete list;
        }
        render();
    }
}


void UI::clear_all()
{
    mToRenderBox.clear();
    render();
}


UI_List * UI::create_list(std::string &title, bool permanent)
{
    auto new_list = new UI_List(title, permanent);
    return new_list;
}


void UI::destroy_list(UI_List * ui_list)
{
    for (int i = 0; i < mToRenderBox.size(); ++i) {
        if (mToRenderBox[i] == ui_list) {
            mToRenderBox.erase(mToRenderBox.begin() + i);
            break;
        }
    }
    render();
    ui_list->clear_items();
    delete ui_list;
}


void UI::push_list(UI_List *ui_list)
{
    mToRenderBox.push_back(ui_list);
}


Box *UI::getLastBox()
{
    if (!isEmpty()) {
        return mToRenderBox.back();
    }
    else {
        return nullptr;
    }
}


bool UI::isEmpty()
{
    return mToRenderBox.empty();
}


UI_List *UI::create_list(int x, int y, int w, int h, std::string &title, bool permanent)
{
    auto new_list = new UI_List(x, y, w, h, title, permanent);
    return new_list;
}


void UISelectUpCommand::execute(Engine *engine)
{
    engine->mUI.getLastBox()->select_next();
}


void UISelectDownCommand::execute(Engine *engine)
{
    engine->mUI.getLastBox()->select_previous();
}


void UISelectedCommand::execute(Engine *engine)
{
    auto command = engine->mUI.getLastBox()->choose();
    if (command != nullptr) {
        engine->pushCommand(command);
    }

}
