#ifndef ABOUT_VIEW_H
#define ABOUT_VIEW_H

#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <functional>

typedef std::function<void()> VoidCallback;

class AboutView : public Fl_Group
{
private:
    Fl_Box m_pTitleBox;
    Fl_Box m_pInfoBox;
    Fl_Button m_pBackButton;

    VoidCallback m_backCallback;

public:
    AboutView(int width, int height);

    static void backCallback(Fl_Widget *widget, void *data);

    void setBackCallback(VoidCallback callback);
};

#endif
