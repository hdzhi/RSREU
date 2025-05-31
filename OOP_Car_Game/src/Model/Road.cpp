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
    // Дорога
    fl_color(FL_BLACK);
    fl_rectf(0, 0, m_width, m_height);

    // Разметка полос
    fl_color(FL_YELLOW);
    for (int lane : m_laneMarkers)
    {
        fl_line(lane, 0, lane, m_height);
    }
}