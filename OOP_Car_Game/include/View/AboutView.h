#ifndef ABOUT_VIEW_H
#define ABOUT_VIEW_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

class AboutController;

class AboutView : public Fl_Window
{
private:
    AboutController *m_pController;
    Fl_Box *m_pTitleBox;
    Fl_Box *m_pInfoBox;
    Fl_Button *m_pBackButton;

public:
    AboutView(int width, int height, const char *title, AboutController *controller);

    static void backCallback(Fl_Widget *widget, void *data);
};

#endif
