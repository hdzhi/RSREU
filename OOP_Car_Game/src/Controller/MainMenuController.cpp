#include "Controller/MainMenuController.h"
#include "Controller/GameController.h"
#include "Controller/AboutController.h"

MainMenuController::MainMenuController(int width, int height, const char *title)
    : m_view(width, height, title, this),
      m_gameController(width, height, this),
      m_aboutController(width, height, this)
{
    m_view.show();
}

void MainMenuController::showMainMenu()
{
    m_view.show();
}

void MainMenuController::startNewGame()
{
    m_view.hide();
    m_gameController.startGame();
}

void MainMenuController::showAbout()
{
    m_view.hide();
    m_aboutController.showAbout();
}

void MainMenuController::exitGame() const
{
    exit(0);
}
