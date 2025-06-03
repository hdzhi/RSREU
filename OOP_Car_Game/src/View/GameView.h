#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <string>

#include "../Model/GameModel.h"

#include <memory>
#include <functional>

typedef std::function<bool(int)> Callback;

class GameView : public Fl_Group
{
private:
    std::shared_ptr<GameModel> m_gameModel;

    Callback m_Callback;

public:
    GameView(int width, int height, std::shared_ptr<GameModel> gameModel);

    void setCallback(Callback callback);

    void draw() override;
    int handle(int event) override;
};

#endif
