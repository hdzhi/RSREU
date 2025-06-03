#include "AboutController.h"
#include "MainController.h"

AboutController::AboutController(MainController *mainController)
    : m_mainController{mainController},
      m_aboutView{std::make_shared<AboutView>(810, 600)}
{
    m_aboutView->setBackCallback(std::bind(&AboutController::backCallback, this));
}

std::shared_ptr<AboutView> AboutController::getAboutView() const
{
    return m_aboutView;
}

void AboutController::backCallback()
{
    m_mainController->changeState(GameState::MENU);
}