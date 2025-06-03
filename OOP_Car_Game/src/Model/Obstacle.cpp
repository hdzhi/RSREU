#include "Obstacle.h"
#include "Car.h"
#include "Obstacle.h"

Obstacle::Obstacle(int line, int screenWidth)
    : m_line{line},
      m_speed{5 + rand() % 5},
      m_width{60},
      m_height{80},
      m_type{rand() % 256}
{
    m_positionX = (m_line + 0.5) * 270;
    m_positionY = -m_height;
}

void Obstacle::update()
{
    m_positionY += m_speed;
}

bool Obstacle::checkCollision(const Car &car) const
{
    int carLeft = car.getPositionX();
    int carRight = carLeft + car.getWidth();
    int carTop = car.getPositionY();
    int carBottom = carTop + car.getHeight();

    int obstacleLeft = m_positionX;
    int obstacleRight = m_positionX + m_width;
    int obstacleTop = m_positionY;
    int obstacleBottom = m_positionY + m_height;

    return (carRight > obstacleLeft &&
            carLeft < obstacleRight &&
            carBottom > obstacleTop &&
            carTop < obstacleBottom);
}

bool Obstacle::isOutOfScreen() const
{
    return m_positionY > 600;
}

int Obstacle::getPositionX() const { return m_positionX; }
int Obstacle::getPositionY() const { return m_positionY; }
int Obstacle::getWidth() const { return m_width; }
int Obstacle::getHeight() const { return m_height; }

void Obstacle::setPassed(bool passed) { m_passed = passed; }
bool Obstacle::getPassed() const { return m_passed; }

int Obstacle::getType() const { return m_type; }