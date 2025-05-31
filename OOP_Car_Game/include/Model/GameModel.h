#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include "Car.h"
#include "Obstacle.h"
#include "Road.h"
#include <vector>
#include <ctime>

class GameModel
{
private:
    Car m_car;
    Road m_road;
    std::vector<Obstacle> m_obstacles;
    int m_score;
    int m_highScore;
    bool m_gameOver;
    time_t m_lastObstacleTime;

public:
    GameModel(int width, int height);

    void update();
    void reset();

    void moveCarLeft();
    void moveCarRight();

    bool isGameOver() const;
    int getScore() const;
    int getHighScore() const;

    const Car &getCar() const;
    const Road &getRoad() const;
    const std::vector<Obstacle> &getObstacles() const;
};

#endif // GAME_MODEL_H