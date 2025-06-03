#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "GameController.h"
#include "MenuController.h"
#include "AboutController.h"

#include "../View/Window.h"

#include <memory>

enum class GameState
{
    MENU,
    GAME,
    ABOUT
};

class MainController
{
private:
    std::shared_ptr<Window> m_window;

    std::shared_ptr<GameModel> m_gameModel;

    std::shared_ptr<GameController> m_gameController;
    std::shared_ptr<MenuController> m_menuController;
    std::shared_ptr<AboutController> m_aboutController;

    GameState m_gameState;

    void showCurrentState();

public:
    MainController();

    int run();

    void changeState(GameState state);
};

#endif