#include "GameView.h"
#include <FL/fl_draw.H>
#include <sstream>

GameView::GameView(int width, int height, std::shared_ptr<GameModel> gameModel)
    : Fl_Group{0, 0, width, height},
      m_gameModel{gameModel}
{
}

void GameView::draw()
{
    std::lock_guard<std::mutex> lock(m_gameModel->getMutex());

    {
        auto road = m_gameModel->getRoad();

        fl_color(FL_BLACK);
        fl_rectf(0, 0, road.getWidth(), road.getHeight());

        fl_color(FL_YELLOW);
        for (int line : road.getLineMarkers())
        {
            fl_line(line, 0, line, road.getHeight());
        }

        fl_color(FL_WHITE);
        for (int y = road.getRoadMarkY(); y < road.getHeight(); y += 40)
        {
            fl_rectf(road.getWidth() / 2 - 25, y, 50, 20);
        }
    }

    {
        auto car = m_gameModel->getCar();
        fl_color(FL_RED);
        fl_rectf(car.getPositionX(), car.getPositionY(), car.getWidth(), car.getHeight());

        fl_color(FL_CYAN);
        fl_rectf(car.getPositionX() + 5, car.getPositionY() + 5, car.getWidth() - 10, car.getHeight() / 3);

        fl_color(FL_YELLOW);
        fl_rectf(car.getPositionX(), car.getPositionY() + car.getHeight() / 3, 5, 5);
        fl_rectf(car.getPositionX() + car.getWidth() - 5, car.getPositionY() + car.getHeight() / 3, 5, 5);
    }

    {
        auto obstacles = m_gameModel->getObstacles();

        for (const auto &obs : obstacles)
        {
            fl_color(static_cast<Fl_Color>(obs.getType()));
            fl_rectf(obs.getPositionX() - obs.getWidth() / 2, obs.getPositionY(), obs.getWidth(), obs.getHeight());

            fl_color(FL_BLACK);
            fl_rect(obs.getPositionX() - obs.getWidth() / 2, obs.getPositionY(), obs.getWidth(), obs.getHeight());
        }
    }

    {
        fl_color(FL_WHITE);
        std::stringstream ss;
        ss << "Счёт: " << m_gameModel->getScore();
        fl_draw(ss.str().c_str(), 20, 40);
    }
}

void GameView::setCallback(Callback callback)
{
    m_Callback = callback;
}

int GameView::handle(int event)
{
    if (m_Callback && m_Callback(event))
    {
        return 1;
    }

    return Fl_Group::handle(event);
}