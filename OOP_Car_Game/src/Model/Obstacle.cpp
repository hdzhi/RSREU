#include "Model/Obstacle.h"
#include "Model/Car.h"
#include "Model/Obstacle.h"

const int LANE_WIDTH = 200;

Obstacle::Obstacle(int lane, int screenWidth)
    : m_lane(lane), m_speed(5 + rand() % 5), m_width(60), m_height(80),
      m_color(static_cast<Fl_Color>(rand() % 256))
{
    m_positionX = (screenWidth - LANE_WIDTH * 3) / 2 + lane * LANE_WIDTH + (LANE_WIDTH - m_width) / 2;
    m_positionY = -m_height;
}

void Obstacle::update()
{
    m_positionY += m_speed;
}

void Obstacle::draw() const
{
    fl_color(m_color);
    fl_rectf(m_positionX - m_width / 2, m_positionY, m_width, m_height);
    fl_color(FL_BLACK);
    fl_rect(m_positionX - m_width / 2, m_positionY, m_width, m_height);
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
