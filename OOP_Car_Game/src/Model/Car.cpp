#include "Car.h"

Car::Car(int positionX, int positionY, int width, int height)
    : m_positionX{positionX},
      m_positionY{positionY},
      m_width{width},
      m_height{height},
      m_currentLine{1} {}

void Car::moveLeft()
{
    if (m_currentLine > 0)
    {
        m_currentLine--;
        m_positionX = (m_currentLine + 0.5) * 270 - 25;
    }
}

void Car::moveRight()
{
    if (m_currentLine < 2)
    {
        m_currentLine++;
        m_positionX = (m_currentLine + 0.5) * 270 - 25;
    }
}

int Car::getPositionX() const { return m_positionX; }
int Car::getPositionY() const { return m_positionY; }
int Car::getWidth() const { return m_width; }
int Car::getHeight() const { return m_height; }
int Car::getCurrentLine() const { return m_currentLine; }

void Car::setPositionX(int positionX) { m_positionX = positionX; }
void Car::setPositionY(int positionY) { m_positionY = positionY; }
