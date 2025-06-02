#include "View/GameView.h"
#include "Controller/GameController.h"
#include <FL/fl_draw.H>
#include <sstream>

GameView::GameView(int width, int height, const char *title, GameController *controller)
    : Fl_Window(width, height, title), m_pController(controller)
{
    begin();

    m_pScoreBox = new Fl_Box(20, 20, 200, 40, "SCORE: 0");
    m_pScoreBox->box(FL_FLAT_BOX);
    m_pScoreBox->labelfont(FL_BOLD);
    m_pScoreBox->labelsize(24);
    m_pScoreBox->labelcolor(FL_WHITE);
    m_pScoreBox->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);

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
    // Надпись GAME OVER
    m_pGameOverBox->resize(this->w() / 2 - 150, this->h() / 2 - 80, 300, 60);
    m_pGameOverBox->copy_label("GAME OVER");
    m_pGameOverBox->labelfont(FL_BOLD);
    m_pGameOverBox->labelsize(48);
    m_pGameOverBox->labelcolor(FL_RED);
    m_pGameOverBox->align(FL_ALIGN_CENTER);

    // Отображаем финальный счет
    Fl_Box *finalScore = new Fl_Box(this->w() / 2 - 150, this->h() / 2 - 20, 300, 40);
    std::stringstream ss;
    ss << "FINAL SCORE: " << m_pScoreBox->label();
    finalScore->copy_label(ss.str().c_str());
    finalScore->labelfont(FL_BOLD);
    finalScore->labelsize(24);
    finalScore->labelcolor(FL_WHITE);
    finalScore->align(FL_ALIGN_CENTER);
    finalScore->show();

    // Кнопка возврата в меню
    m_pBackButton->resize(this->w() / 2 - 75, this->h() / 2 + 40, 150, 40);
    m_pBackButton->copy_label("MAIN MENU");
    m_pBackButton->color(FL_DARK_BLUE);
    m_pBackButton->labelfont(FL_BOLD);
    m_pBackButton->labelsize(18);
    m_pBackButton->labelcolor(FL_WHITE);

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
