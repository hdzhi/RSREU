#include "Model/GameModel.h"
#include <ctime>
#include <algorithm>    // Добавляем для std::remove_if
#include "Model/Road.h" // Убедитесь, что этот файл существует и содержит getWidth()

GameModel::GameModel(int width, int height)
    : m_car(width / 2 - 25, height - 100, 50, 80, FL_RED),
      m_road(width, height),
      m_score(0),
      m_highScore(0),
      m_gameOver(false),
      m_lastObstacleTime(time(nullptr)) {}

void GameModel::update()
{
    if (m_gameOver)
        return;

    m_road.update();

    // Добавление новых препятствий
    time_t currentTime = time(nullptr);
    if (currentTime - m_lastObstacleTime > 1)
    {
        int lane = rand() % 3;
        m_obstacles.emplace_back(lane, m_road.getHeight());
        m_lastObstacleTime = currentTime;
    }

    // Обновление препятствий
    for (auto &obstacle : m_obstacles)
    {
        obstacle.update();

        // Проверка столкновений
        if (obstacle.checkCollision(m_car))
        {
            m_gameOver = true;
            if (m_score > m_highScore)
            {
                m_highScore = m_score;
            }
            return;
        }
    }

    // Удаление препятствий за пределами экрана
    m_obstacles.erase(
        std::remove_if(m_obstacles.begin(), m_obstacles.end(),
                       [](const Obstacle &o)
                       { return o.isOutOfScreen(); }),
        m_obstacles.end());

    // Увеличение счета
    m_score++;
}

void GameModel::reset()
{
    m_car = Car(m_road.getWidth() / 2 - 25, m_road.getHeight() - 100, 50, 80, FL_RED);
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