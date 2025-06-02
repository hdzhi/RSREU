#ifndef ABOUT_CONTROLLER_H
#define ABOUT_CONTROLLER_H

#include "View/AboutView.h"

class MainMenuController;

class AboutController
{
private:
    AboutView m_view;
    MainMenuController *m_pMainMenuController;

public:
    AboutController(int width, int height, MainMenuController *mainMenuController);

    void showAbout();
    void backToMenu();
    AboutView &getView() { return m_view; }
};

#endif // ABOUT_CONTROLLER_H
