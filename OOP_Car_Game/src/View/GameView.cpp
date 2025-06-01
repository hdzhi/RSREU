#include "View/GameView.h"
#include "Controller/GameController.h"
#include <FL/fl_draw.H>
#include <sstream>

GameView::GameView(int width, int height, const char *title, GameController *controller)
    : Fl_Window(width, height, title), m_pController(controller)
{
    begin();

    m_pScoreBox = new Fl_Box(10, 10, 200, 30, "Score: 0");
    m_pScoreBox->labelfont(FL_BOLD);
    m_pScoreBox->labelsize(18);
    m_pScoreBox->labelcolor(FL_WHITE);

    m_pHighScoreBox = new Fl_Box(width - 210, 10, 200, 30, "High Score: 0");
    m_pHighScoreBox->labelfont(FL_BOLD);
    m_pHighScoreBox->labelsize(18);
    m_pHighScoreBox->labelcolor(FL_WHITE);
    m_pHighScoreBox->align(FL_ALIGN_RIGHT);

    m_pGameOverBox = new Fl_Box(width / 2 - 150, height / 2 - 50, 300, 100, "GAME OVER");
    m_pGameOverBox->labelfont(FL_BOLD);
    m_pGameOverBox->labelsize(36);
    m_pGameOverBox->labelcolor(FL_RED);
    m_pGameOverBox->hide();

    m_pBackButton = new Fl_Button(width / 2 - 50, height / 2 + 60, 100, 30, "Back to Menu");
    m_pBackButton->callback(backToMenuCallback, this);
    m_pBackButton->hide();

    end();
}

void GameView::draw()
{
    Fl_Window::draw();
    m_pController->drawGame();
}

void GameView::updateScore(int score)
{
    std::stringstream ss;
    ss << "Score: " << score;
    m_pScoreBox->copy_label(ss.str().c_str());
    redraw();
}

void GameView::updateHighScore(int highScore)
{
    std::stringstream ss;
    ss << "High Score: " << highScore;
    m_pHighScoreBox->copy_label(ss.str().c_str());
    redraw();
}

void GameView::showGameOver()
{
    m_pGameOverBox->show();
    m_pBackButton->show();
    redraw();
}

void GameView::hideGameOver()
{
    m_pGameOverBox->hide();
    m_pBackButton->hide();
    redraw();
}

void GameView::backToMenuCallback(Fl_Widget *widget, void *data)
{
    GameView *view = static_cast<GameView *>(data);
    view->m_pController->backToMenu();
}

int GameView::handle(int event)
{
    if (event == FL_KEYDOWN)
    {
        m_pController->handleKeyPress(Fl::event_key());
        return 1;
    }
    return Fl_Window::handle(event);
}
