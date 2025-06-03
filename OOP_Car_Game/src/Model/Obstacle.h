#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <cstdlib>

class Car;

class Obstacle
{
private:
    int m_positionX;
    int m_positionY;
    int m_width;
    int m_height;
    int m_speed;
    int m_line;
    int m_type;
    bool m_passed;

public:
    Obstacle(int line, int screenHeight);

    void update();
    bool checkCollision(const Car &car) const;
    bool isOutOfScreen() const;
    bool getPassed() const;

    int getPositionX() const;
    int getPositionY() const;
    int getWidth() const;
    int getHeight() const;
    void setPassed(bool passed);
    int getType() const;
};

#endif
