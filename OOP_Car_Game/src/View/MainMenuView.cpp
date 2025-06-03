#include "MainMenuView.h"
#include <FL/fl_draw.H>

MainMenuView::MainMenuView(int width, int height)
    : Fl_Group{0, 0, width, height},
      m_pTitleBox{0, 100, width, 80, "RACING GAME"},
      m_pNewGameButton{width / 2 - 100, 250, 200, 50, "NEW GAME"},
      m_pAboutButton{width / 2 - 100, 320, 200, 50, "ABOUT"},
      m_pExitButton{width / 2 - 100, 390, 200, 50, "EXIT"}
{
    begin();

    box(FL_FLAT_BOX);
    color(fl_rgb_color(30, 30, 40));

    m_pTitleBox.labelfont(FL_BOLD);
    m_pTitleBox.labelsize(48);
    m_pTitleBox.labelcolor(FL_YELLOW);
    m_pTitleBox.align(FL_ALIGN_CENTER);

    m_pNewGameButton.color(FL_DARK_GREEN);
    m_pNewGameButton.labelfont(FL_BOLD);
    m_pNewGameButton.labelsize(24);
    m_pNewGameButton.labelcolor(FL_WHITE);
    m_pNewGameButton.callback(newGameCallback, this);

    m_pAboutButton.color(FL_DARK_BLUE);
    m_pAboutButton.labelfont(FL_BOLD);
    m_pAboutButton.labelsize(24);
    m_pAboutButton.labelcolor(FL_WHITE);
    m_pAboutButton.callback(aboutCallback, this);

    m_pExitButton.color(FL_DARK_RED);
    m_pExitButton.labelfont(FL_BOLD);
    m_pExitButton.labelsize(24);
    m_pExitButton.labelcolor(FL_WHITE);
    m_pExitButton.callback(exitCallback, this);

    end();
}

void MainMenuView::newGameCallback(Fl_Widget *widget, void *data)
{
    MainMenuView *view = static_cast<MainMenuView *>(data);

    if (view->m_newGameCallback)
        view->m_newGameCallback();
}

void MainMenuView::aboutCallback(Fl_Widget *widget, void *data)
{
    MainMenuView *view = static_cast<MainMenuView *>(data);

    if (view->m_aboutCallback)
        view->m_aboutCallback();
}

void MainMenuView::exitCallback(Fl_Widget *widget, void *data)
{
    MainMenuView *view = static_cast<MainMenuView *>(data);

    if (view->m_exitCallback)
        view->m_exitCallback();
}

void MainMenuView::setNewGameCallback(VoidCallback callback)
{
    m_newGameCallback = callback;
}

void MainMenuView::setAboutCallback(VoidCallback callback)
{
    m_aboutCallback = callback;
}

void MainMenuView::setExitCallback(VoidCallback callback)
{
    m_exitCallback = callback;
}