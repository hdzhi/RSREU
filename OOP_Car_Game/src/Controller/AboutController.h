#ifndef ABOUT_CONTROLLER_H
#define ABOUT_CONTROLLER_H

#include "../View/AboutView.h"

#include <memory>

class MainController;

class AboutController
{
private:
    std::shared_ptr<AboutView> m_aboutView;

    MainController *m_mainController;

    void backCallback();

public:
    AboutController(MainController *mainController);

    std::shared_ptr<AboutView> getAboutView() const;
};

#endif