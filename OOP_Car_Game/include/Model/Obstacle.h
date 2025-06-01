#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <cstdlib>

class Car;

enum class ObstacleType
{
    CAR,
    TRUCK,
    CONE
};

class Obstacle
{
private:
    int m_positionX;
    int m_positionY;
    int m_width;
    int m_height;
    int m_speed;
    Fl_Color m_color;
    int m_lane;

public:
    Obstacle(int lane, int screenHeight);

    void update();
    void draw() const;
    bool checkCollision(const Car &car) const;
    bool isOutOfScreen() const;

    int getPositionX() const;
    int getPositionY() const;
    int getWidth() const;
    int getHeight() const;
};

#endif
