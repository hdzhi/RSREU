#include "AboutView.h"

const char *infoText =
    "RACING GAME\n\n"
    "Avoid obstacles by switching lines.\n"
    "Use LEFT and RIGHT arrow keys to move.\n\n"
    "Created with FLTK library\n";

AboutView::AboutView(int width, int height)
    : Fl_Group{0, 0, width, height},
      m_pTitleBox{0, 50, width, 60, "ABOUT"},
      m_pInfoBox{50, 150, width - 100, 200, infoText},
      m_pBackButton{width / 2 - 100, height - 100, 200, 50, "BACK TO MENU"}
{
    begin();

    box(FL_FLAT_BOX);
    color(fl_rgb_color(30, 30, 40));

    m_pTitleBox.labelfont(FL_BOLD);
    m_pTitleBox.labelsize(36);
    m_pTitleBox.labelcolor(FL_YELLOW);
    m_pTitleBox.align(FL_ALIGN_CENTER);

    m_pInfoBox.labelfont(FL_BOLD);
    m_pInfoBox.labelsize(18);
    m_pInfoBox.labelcolor(FL_WHITE);
    m_pInfoBox.align(FL_ALIGN_CENTER | FL_ALIGN_TOP | FL_ALIGN_INSIDE | FL_ALIGN_WRAP);

    m_pBackButton.color(FL_DARK_BLUE);
    m_pBackButton.labelfont(FL_BOLD);
    m_pBackButton.labelsize(24);
    m_pBackButton.labelcolor(FL_WHITE);
    m_pBackButton.callback(backCallback, this);

    end();
}

void AboutView::backCallback(Fl_Widget *widget, void *data)
{
    AboutView *view = static_cast<AboutView *>(data);

    if (view->m_backCallback)
        view->m_backCallback();
}

void AboutView::setBackCallback(VoidCallback callback)
{
    m_backCallback = callback;
}