#include "View/MainMenuView.h"
#include "Controller/MainMenuController.h"
#include <FL/fl_draw.H>

MainMenuView::MainMenuView(int width, int height, const char *title, MainMenuController *controller)
    : Fl_Window(width, height, title), m_pController(controller)
{
    begin();

    // Красивый фон
    box(FL_FLAT_BOX);
    color(fl_rgb_color(30, 30, 40));

    m_pTitleBox = new Fl_Box(0, 100, width, 80, "RACING GAME");
    m_pTitleBox->labelfont(FL_BOLD);
    m_pTitleBox->labelsize(48);
    m_pTitleBox->labelcolor(FL_YELLOW);
    m_pTitleBox->align(FL_ALIGN_CENTER);

    m_pNewGameButton = new Fl_Button(width / 2 - 100, 250, 200, 50, "NEW GAME");
    m_pNewGameButton->color(FL_DARK_GREEN);
    m_pNewGameButton->labelfont(FL_BOLD);
    m_pNewGameButton->labelsize(24);
    m_pNewGameButton->labelcolor(FL_WHITE);
    m_pNewGameButton->callback(newGameCallback, this);

    m_pAboutButton = new Fl_Button(width / 2 - 100, 320, 200, 50, "ABOUT");
    m_pAboutButton->color(FL_DARK_BLUE);
    m_pAboutButton->labelfont(FL_BOLD);
    m_pAboutButton->labelsize(24);
    m_pAboutButton->labelcolor(FL_WHITE);
    m_pAboutButton->callback(aboutCallback, this);

    m_pExitButton = new Fl_Button(width / 2 - 100, 390, 200, 50, "EXIT");
    m_pExitButton->color(FL_DARK_RED);
    m_pExitButton->labelfont(FL_BOLD);
    m_pExitButton->labelsize(24);
    m_pExitButton->labelcolor(FL_WHITE);
    m_pExitButton->callback(exitCallback, this);

    end();
}

void MainMenuView::newGameCallback(Fl_Widget *widget, void *data)
{
    MainMenuView *view = static_cast<MainMenuView *>(data);
    view->m_pController->startNewGame();
}

void MainMenuView::aboutCallback(Fl_Widget *widget, void *data)
{
    MainMenuView *view = static_cast<MainMenuView *>(data);
    view->m_pController->showAbout();
}

void MainMenuView::exitCallback(Fl_Widget *widget, void *data)
{
    MainMenuView *view = static_cast<MainMenuView *>(data);
    view->m_pController->exitGame();
}