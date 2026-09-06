#include "Grid.h"

std::array<int, 26> Grid::preComputeCellsOffset(size_t w, size_t h)
{
    int idx = 0;
    std::array<int, 26> offset{};

    int ww = static_cast<int>(w);
    int hh = static_cast<int>(h);

    printf(">>> ww=%d, hh=%d\n", ww, hh);

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
                    printf(">>> (%d,%d,%d) -> %d\n", dx, dy, dz, offset[idx]);
                    idx++;
                }
            }
        }
    }

    return offset;
}