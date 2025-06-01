#ifndef ROAD_H
#define ROAD_H

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <vector>

class Road
{
private:
    int m_width;
    int m_height;
    std::vector<int> m_laneMarkers;
    int m_roadMarkY;

public:
    Road(int width, int height);

    void update();
    void draw() const;

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
};

#endif
