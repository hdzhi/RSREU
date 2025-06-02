#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <string>

class GameController;

class GameView : public Fl_Window
{
private:
    GameController *m_pController;
    Fl_Box *m_pScoreBox;
    Fl_Box *m_pHighScoreBox;
    Fl_Box *m_pGameOverBox;
    Fl_Button *m_pBackButton;

public:
    GameView(int width, int height, const char *title, GameController *controller);

    void draw() override;
    void updateScore(int score);
    void updateHighScore(int highScore);
    void showGameOver();
    void hideGameOver();
    void showFinalScore(int score);

    static void backToMenuCallback(Fl_Widget *widget, void *data);
    int handle(int event) override;
};

#endif
