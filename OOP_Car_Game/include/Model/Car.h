#ifndef CAR_H
#define CAR_H

#include <FL/Fl.H>
#include <FL/fl_draw.H>

class Car
{
private:
    int m_positionX;
    int m_positionY;
    int m_width;
    int m_height;
    int m_currentLane;
    Fl_Color m_color;

public:
    Car(int positionX, int positionY, int width, int height, Fl_Color color);

    void moveLeft();
    void moveRight();
    void draw() const;

    int getPositionX() const;
    int getPositionY() const;
    int getWidth() const;
    int getHeight() const;
    int getCurrentLane() const;

    void setCurrentLane(int lane) { m_currentLane = lane; }
    void setPositionX(int positionX);
    void setPositionY(int positionY);
};

#endif
