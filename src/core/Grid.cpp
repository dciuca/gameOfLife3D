#include "Grid.h"

std::array<int, 26> Grid::preComputeCellsOffset(size_t w, size_t h)
{
    int idx = 0;
    std::array<int, 26> offset{};

    int ww = static_cast<int>(w);
    int hh = static_cast<int>(h);

    for (int dz = -1; dz <= 1; dz++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            for (int dx = -1; dx <= 1; dx++)
            {
                if (dz == 0 && dy == 0 && dx == 0)
                    continue;
                else
                {
                    offset[idx] = dx + dy * ww + dz * ww * hh;
                    idx++;
                }
            }
        }
    }

    return offset;
}

void Grid::setCellByPosition(size_t x, size_t y, size_t z, uint8_t value)
{
    size_t idx = x + y * m_width + z * m_width * m_height;
    m_grid[idx] = value;
}