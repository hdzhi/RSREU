#include "Model/Road.h"

Road::Road(int width, int height)
    : m_width(width), m_height(height), m_roadMarkY(0)
{
    m_laneMarkers = {width / 3, 2 * width / 3};
}

void Road::update()
{
    m_roadMarkY += 5;
    if (m_roadMarkY > 40)
    {
        m_roadMarkY = 0;
    }
}

void Road::draw() const
{
    fl_color(FL_BLACK);
    fl_rectf(0, 0, m_width, m_height);

    fl_color(FL_YELLOW);
    for (int lane : m_laneMarkers)
    {
        fl_line(lane, 0, lane, m_height);
    }

    fl_color(FL_WHITE);
    for (int y = m_roadMarkY; y < m_height; y += 40)
    {
        fl_rectf(m_width / 2 - 25, y, 50, 20);
    }
}
