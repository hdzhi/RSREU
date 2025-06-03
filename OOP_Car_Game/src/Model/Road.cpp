#include "Road.h"

Road::Road(int width, int height)
    : m_width{width},
      m_height{height},
      m_roadMarkY{0},
      m_lineMarkers{width / 3, 2 * width / 3}
{
}

void Road::update()
{
    m_roadMarkY += 5;
    if (m_roadMarkY > 40)
    {
        m_roadMarkY = 0;
    }
}