#include "Controller/GameController.h"
#include "Controller/MainMenuController.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

GameController::GameController(int width, int height, MainMenuController *mainMenuController)
    : m_model(width, height),
      m_view(width, height, "Racing Game - Play Mode", this),
      m_pMainMenuController(mainMenuController) {}

void GameController::startGame()
{
    m_model.reset();
    m_view.show();
    m_view.hideGameOver();
    Fl::add_timeout(0.016, timerCallback, this); // ~60 FPS
}

void GameController::backToMenu()
{
    m_view.hide();
    m_pMainMenuController->showMainMenu();
    Fl::remove_timeout(timerCallback, this);
}

void GameController::handleKeyPress(int key)
{
    switch (key)
    {
    case FL_Left:
        m_model.moveCarLeft();
        break;
    case FL_Right:
        m_model.moveCarRight();
        break;
    }
}

void GameController::drawGame() const
{
    // Отрисовка игры
    m_model.getRoad().draw();

    for (const auto &obstacle : m_model.getObstacles())
    {
        obstacle.draw();
    }

    m_model.getCar().draw();
}

void GameController::timerCallback(void *data)
{
    GameController *controller = static_cast<GameController *>(data);

    controller->m_model.update();
    controller->m_view.updateScore(controller->m_model.getScore());

    if (controller->m_model.isGameOver())
    {
        controller->m_view.updateHighScore(controller->m_model.getHighScore());
        controller->m_view.showGameOver();
        Fl::remove_timeout(timerCallback, data);
    }
    else
    {
        Fl::repeat_timeout(0.016, timerCallback, data);
    }

    controller->m_view.redraw();
}

GameView &GameController::getView()
{
    return m_view;
}