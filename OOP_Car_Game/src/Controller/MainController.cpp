#include "MainController.h"

MainController::MainController()
    : m_window{std::make_shared<Window>(0, 0, 810, 600, "Racing Game")},
      m_gameModel{std::make_shared<GameModel>(810, 600)},
      m_gameController{std::make_shared<GameController>(m_gameModel, this)},
      m_menuController{std::make_shared<MenuController>(m_gameModel, this)},
      m_aboutController{std::make_shared<AboutController>(this)}
{
    m_window->begin();

    m_window->add(m_gameController->getGameView().get());
    m_window->add(m_menuController->getMainMenuView().get());
    m_window->add(m_aboutController->getAboutView().get());

    m_window->end();

    changeState(GameState::MENU);
}

int MainController::run()
{
    m_window->show();
    return Fl::run();
}

void MainController::changeState(GameState state)
{
    m_gameState = state;

    showCurrentState();
}

void MainController::showCurrentState()
{
    m_menuController->getMainMenuView()->hide();
    m_gameController->getGameView()->hide();
    m_aboutController->getAboutView()->hide();

    switch (m_gameState)
    {
    case GameState::MENU:
        m_menuController->getMainMenuView()->show();
        break;
    case GameState::GAME:
        m_gameController->getGameView()->show();
        break;
    case GameState::ABOUT:
        m_aboutController->getAboutView()->show();
        break;
    }
}