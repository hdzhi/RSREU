#ifndef MAIN_MENU_VIEW_H
#define MAIN_MENU_VIEW_H

#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <functional>

typedef std::function<void()> VoidCallback;

class MainMenuView : public Fl_Group
{
private:
    Fl_Box m_pTitleBox;
    Fl_Button m_pNewGameButton;
    Fl_Button m_pAboutButton;
    Fl_Button m_pExitButton;

    VoidCallback m_newGameCallback;
    VoidCallback m_aboutCallback;
    VoidCallback m_exitCallback;

public:
    MainMenuView(int width, int height);

    static void newGameCallback(Fl_Widget *widget, void *data);
    static void aboutCallback(Fl_Widget *widget, void *data);
    static void exitCallback(Fl_Widget *widget, void *data);

    void setNewGameCallback(VoidCallback callback);
    void setAboutCallback(VoidCallback callback);
    void setExitCallback(VoidCallback callback);
};

#endif
