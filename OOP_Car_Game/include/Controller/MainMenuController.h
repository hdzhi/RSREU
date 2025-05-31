#ifndef MAIN_MENU_CONTROLLER_H
#define MAIN_MENU_CONTROLLER_H

#include "View/MainMenuView.h"
#include "Controller/GameController.h"
#include "Controller/AboutController.h"

class MainMenuController
{
private:
    MainMenuView m_view;
    GameController m_gameController;
    AboutController m_aboutController;

public:
    MainMenuController(int width, int height, const char *title);

    void showMainMenu();
    void startNewGame();
    void showAbout();
    void exitGame() const;
};

#endif // MAIN_MENU_CONTROLLER_H