#include "MenuController.h"
#include "MainController.h"

MenuController::MenuController(std::shared_ptr<GameModel> model, MainController *mainController)
    : m_gameModel{model},
      m_mainMenuView{std::make_shared<MainMenuView>(810, 600)},
      m_mainController{mainController}
{
    m_mainMenuView->setNewGameCallback(std::bind(&MenuController::newGameCallback, this));
    m_mainMenuView->setAboutCallback(std::bind(&MenuController::aboutCallback, this));
    m_mainMenuView->setExitCallback(std::bind(&MenuController::exitCallback, this));
}

std::shared_ptr<GameModel> MenuController::getGameModel() const
{
    return m_gameModel;
}

std::shared_ptr<MainMenuView> MenuController::getMainMenuView() const
{
    return m_mainMenuView;
}

void MenuController::newGameCallback()
{
    m_gameModel->reset();
    m_mainController->changeState(GameState::GAME);
}

void MenuController::aboutCallback()
{
    m_mainController->changeState(GameState::ABOUT);
}

void MenuController::exitCallback()
{
    exit(0);
}