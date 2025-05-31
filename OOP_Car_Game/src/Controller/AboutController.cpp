#include "Controller/AboutController.h"
#include "Controller/MainMenuController.h"

AboutController::AboutController(int width, int height, MainMenuController *mainMenuController)
    : m_view(width, height, "Racing Game - About", this),
      m_pMainMenuController(mainMenuController) {}

void AboutController::showAbout()
{
    m_view.show();
}

void AboutController::backToMenu()
{
    m_view.hide();
    m_pMainMenuController->showMainMenu();
}