#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "../View/GameView.h"
#include "../Model/GameModel.h"

class MainController;

class GameController
{
private:
    std::shared_ptr<GameModel> m_gameModel;
    std::shared_ptr<GameView> m_gameView;

    MainController *m_mainController;

public:
    GameController(std::shared_ptr<GameModel> model, MainController *mainController);

    std::shared_ptr<GameModel> getGameModel() const;
    std::shared_ptr<GameView> getGameView() const;

    bool eventCallback(int event);
    void gameOverCallback();
};

#endif