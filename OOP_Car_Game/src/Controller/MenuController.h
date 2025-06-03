#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include "../View/MainMenuView.h"
#include "../Model/GameModel.h"

#include <memory>

class MainController;

class MenuController
{
private:
    std::shared_ptr<GameModel> m_gameModel;
    std::shared_ptr<MainMenuView> m_mainMenuView;

    MainController *m_mainController;

    void newGameCallback();
    void aboutCallback();
    void exitCallback();

public:
    MenuController(std::shared_ptr<GameModel> model, MainController *mainController);

    std::shared_ptr<GameModel> getGameModel() const;
    std::shared_ptr<MainMenuView> getMainMenuView() const;
};

#endif