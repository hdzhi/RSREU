#include "GameController.h"
#include "MainController.h"

#include <iostream>

GameController::GameController(std::shared_ptr<GameModel> model, MainController *mainController)
    : m_mainController{mainController},
      m_gameModel{model},
      m_gameView{std::make_shared<GameView>(810, 600, m_gameModel)}
{
    m_gameView->setCallback(std::bind(&GameController::eventCallback, this, std::placeholders::_1));

    m_gameModel->setCallback(std::bind(&GameController::gameOverCallback, this));
}

std::shared_ptr<GameModel> GameController::getGameModel() const
{
    return m_gameModel;
}

std::shared_ptr<GameView> GameController::getGameView() const
{
    return m_gameView;
}

bool GameController::eventCallback(int event)
{
    int key = Fl::event_key();

    switch (event)
    {
    case FL_FOCUS:
    case FL_UNFOCUS:
        return true;
    case FL_KEYDOWN:
        switch (key)
        {
        case FL_Left:
            m_gameModel->moveCarLeft();
            return true;
        case FL_Right:
            m_gameModel->moveCarRight();
            return true;
        }
        break;

    default:
        break;
    }

    return false;
}

void GameController::gameOverCallback()
{
    m_mainController->changeState(GameState::MENU);
}