#include "core/Grid.h"

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

void Grid::updateGuardCells()
{
    // Need at least one interior cell per axis
    if (m_width < 3 || m_height < 3 || m_depth < 3)
        return;

    const size_t w = m_width;
    const size_t h = m_height;
    const size_t d = m_depth;
    const size_t wh = w * h;
    uint8_t *data = m_grid.data();

    // Physical size >= 5 <=> logical size >= 3
    const bool wrapX = w >= 5;
    const bool wrapY = h >= 5;
    const bool wrapZ = d >= 5;

    // The axes are processed in order X -> Y -> Z, each pass copying whole
    // rows/slices that include the guards filled by the previous passes,
    // so edges and corners end up correct too.

    // X faces: first and last cell of every row
    for (size_t row = 0; row < h * d; row++)
    {
        uint8_t *r = data + row * w;
        r[0] = wrapX ? r[w - 2] : 0;
        r[w - 1] = wrapX ? r[1] : 0;
    }

    // Y faces: first and last row of every z slice
    for (size_t z = 0; z < d; z++)
    {
        uint8_t *slice = data + z * wh;
        if (wrapY)
        {
            std::copy_n(slice + (h - 2) * w, w, slice);
            std::copy_n(slice + w, w, slice + (h - 1) * w);
        }
        else
        {
            std::fill_n(slice, w, 0);
            std::fill_n(slice + (h - 1) * w, w, 0);
        }
    }

    // Z faces: first and last slice
    if (wrapZ)
    {
        std::copy_n(data + (d - 2) * wh, wh, data);
        std::copy_n(data + wh, wh, data + (d - 1) * wh);
    }
    else
    {
        std::fill_n(data, wh, 0);
        std::fill_n(data + (d - 1) * wh, wh, 0);
    }
}