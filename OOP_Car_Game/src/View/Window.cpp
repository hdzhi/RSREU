#include "Window.h"

Window::Window(int x, int y, int w, int h, const char *l)
    : Fl_Double_Window{x, y, w, h, l}
{
    Fl::add_timeout(1.0 / FPS, Timer_CB, this);
}

void Window::Timer_CB(void *data)
{
    auto *window = static_cast<Window *>(data);
    window->redraw();

    Fl::repeat_timeout(1.0 / FPS, Timer_CB, window);
}