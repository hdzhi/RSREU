#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include "Car.h"
#include "Obstacle.h"
#include "Road.h"
#include <vector>
#include <ctime>

#include <thread>
#include <mutex>
#include <functional>

typedef std::function<void()> VoidCallback;

class GameModel
{
private:
    Car m_car;
    Road m_road;
    std::vector<Obstacle> m_obstacles;
    int m_obstacleWaveCount;
    double m_nextWaveTime;
    int m_score;
    int m_highScore;
    bool m_gameOver;
    time_t m_lastObstacleTime;
    std::thread m_updateThread;
    std::mutex m_mutex;

    VoidCallback m_gameOverCallback;

    bool m_isClosed;

    void updateThread();

public:
    GameModel(int width, int height);
    ~GameModel();

    void update();
    void reset();

    void moveCarLeft();
    void moveCarRight();

    bool isGameOver() const;
    int getScore() const;
    int getHighScore() const;

    std::mutex &getMutex();

    const Car &getCar() const;
    const Road &getRoad() const;
    const std::vector<Obstacle> &getObstacles() const;

    void setCallback(VoidCallback callback);
};

#endif
