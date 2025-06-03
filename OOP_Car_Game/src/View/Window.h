#ifndef WINDOW_H
#define WINDOW_H

#include "FL/Fl_Double_Window.H"

const float FPS = 60.0;

class Window : public Fl_Double_Window
{
private:
    static void Timer_CB(void *data);

public:
    Window(int x, int y, int w, int h, const char *l = 0);
};

#endif