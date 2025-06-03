#ifndef CAR_H
#define CAR_H

class Car
{
private:
    int m_positionX;
    int m_positionY;
    int m_width;
    int m_height;
    int m_currentLine;

public:
    Car(int positionX, int positionY, int width, int height);

    void moveLeft();
    void moveRight();

    int getPositionX() const;
    int getPositionY() const;
    int getWidth() const;
    int getHeight() const;
    int getCurrentLine() const;

    void setCurrentLine(int line) { m_currentLine = line; }
    void setPositionX(int positionX);
    void setPositionY(int positionY);
};

#endif
