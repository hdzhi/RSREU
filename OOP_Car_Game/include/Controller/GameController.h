#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "View/GameView.h"
#include "Model/GameModel.h"
#include <FL/Fl.H>

class MainMenuController;

class GameController
{
private:
    GameModel m_model;
    GameView m_view;
    MainMenuController *m_pMainMenuController;

    static void timerCallback(void *data);

public:
    GameController(int width, int height, MainMenuController *mainMenuController);

    void startGame();
    void backToMenu();
    void handleKeyPress(int key);
    void drawGame() const;

    GameView &getView();
};

#endif
