#include "Model/Car.h"

Car::Car(int positionX, int positionY, int width, int height, Fl_Color color)
    : m_positionX(positionX), m_positionY(positionY), m_width(width), m_height(height),
      m_currentLane(1), m_color(color) {}

void Car::moveLeft()
{
    if (m_currentLane > 0)
    {
        m_currentLane--;
        m_positionX -= 100; // Ширина полосы
    }
}

void Car::moveRight()
{
    if (m_currentLane < 2)
    {
        m_currentLane++;
        m_positionX += 100; // Ширина полосы
    }
}

void Car::draw() const
{
    // Кузов машины
    fl_color(m_color);
    fl_rectf(m_positionX, m_positionY, m_width, m_height);

    // Окна машины
    fl_color(FL_CYAN);
    fl_rectf(m_positionX + 5, m_positionY + 5, m_width - 10, m_height / 3);

    // Фары
    fl_color(FL_YELLOW);
    fl_rectf(m_positionX, m_positionY + m_height / 3, 5, 5);
    fl_rectf(m_positionX + m_width - 5, m_positionY + m_height / 3, 5, 5);
}

int Car::getPositionX() const { return m_positionX; }
int Car::getPositionY() const { return m_positionY; }
int Car::getWidth() const { return m_width; }
int Car::getHeight() const { return m_height; }
int Car::getCurrentLane() const { return m_currentLane; }

void Car::setPositionX(int positionX) { m_positionX = positionX; }
void Car::setPositionY(int positionY) { m_positionY = positionY; }