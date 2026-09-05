#include "Grid.h"

std::array<int32_t, 26> Grid::preComputeCellsOffset(size_t w, size_t h)
{
    int idx = 0;
    std::array<int32_t, 26> offset{};

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
                    offset[idx++] = dx + dy * w + dz * w * h;
                }
            }
        }
    }

    return offset;
}