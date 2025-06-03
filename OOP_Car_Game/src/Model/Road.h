#ifndef ROAD_H
#define ROAD_H

#include <vector>

class Road
{
private:
    int m_width;
    int m_height;
    std::vector<int> m_lineMarkers;
    int m_roadMarkY;

public:
    Road(int width, int height);

    void update();

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    std::vector<int> getLineMarkers() const { return m_lineMarkers; }
    int getRoadMarkY() const { return m_roadMarkY; }
};

#endif
