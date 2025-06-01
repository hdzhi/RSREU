#ifndef MAIN_MENU_VIEW_H
#define MAIN_MENU_VIEW_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

class MainMenuController;

class MainMenuView : public Fl_Window
{
private:
    MainMenuController *m_pController;
    Fl_Box *m_pTitleBox;
    Fl_Button *m_pNewGameButton;
    Fl_Button *m_pAboutButton;
    Fl_Button *m_pExitButton;

public:
    MainMenuView(int width, int height, const char *title, MainMenuController *controller);

    static void newGameCallback(Fl_Widget *widget, void *data);
    static void aboutCallback(Fl_Widget *widget, void *data);
    static void exitCallback(Fl_Widget *widget, void *data);
};

#endif
