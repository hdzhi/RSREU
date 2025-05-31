#include <FL/Fl.H>
#include "Controller/MainMenuController.h"

int main(int argc, char **argv)
{
    MainMenuController mainMenuController(800, 600, "Racing Game");
    return Fl::run();
}