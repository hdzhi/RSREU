#include "Model/GameModel.h"
#include <ctime>
#include <algorithm>
#include "Model/Road.h"

GameModel::GameModel(int width, int height)
    : m_car(width, height - 150, 50, 80, FL_RED),
      m_road(width, height),
      m_score(0),
      m_highScore(0),
      m_gameOver(false),
      m_lastObstacleTime(time(nullptr))
{
    m_car.setPositionX(width / 2 - 25);
}

void GameModel::update()
{
    if (m_gameOver)
        return;

    m_road.update();

    if (time(nullptr) - m_lastObstacleTime > 0.3)
    {
        int lane = rand() % 3;
        m_obstacles.emplace_back(lane, m_road.getWidth());
        m_lastObstacleTime = time(nullptr);
    }

    for (auto &obstacle : m_obstacles)
    {
        obstacle.update();
        if (obstacle.checkCollision(m_car))
        {
            m_gameOver = true;
            m_highScore = std::max(m_score, m_highScore);
            return;
        }
    }

    m_obstacles.erase(
        std::remove_if(m_obstacles.begin(), m_obstacles.end(),
                       [](const Obstacle &o)
                       { return o.isOutOfScreen(); }),
        m_obstacles.end());

    m_score++;
}

void GameModel::reset()
{
    m_car = Car(m_road.getWidth() / 2 - 25, m_road.getHeight() - 100, 50, 80, FL_RED);
    m_car.setPositionX(m_road.getWidth() / 2 - 25);
    m_obstacles.clear();
    m_score = 0;
    m_gameOver = false;
    m_lastObstacleTime = time(nullptr);
}

void GameModel::moveCarLeft()
{
    if (!m_gameOver)
    {
        m_car.moveLeft();
    }
}

void GameModel::moveCarRight()
{
    if (!m_gameOver)
    {
        m_car.moveRight();
    }
}

bool GameModel::isGameOver() const
{
    return m_gameOver;
}

int GameModel::getScore() const
{
    return m_score;
}

int GameModel::getHighScore() const
{
    return m_highScore;
}

const Car &GameModel::getCar() const
{
    return m_car;
}

const Road &GameModel::getRoad() const
{
    return m_road;
}

const std::vector<Obstacle> &GameModel::getObstacles() const
{
    return m_obstacles;
}
