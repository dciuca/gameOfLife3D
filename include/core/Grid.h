#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>
#include <array>

/**
 * @class Grid
 * @brief Represents a dense 3D grid of cells.
 *
 * Cells are stored in a single flat `std::vector<uint8_t>` to keep memory
 * contiguous and access fast. The flat index for a 3D coordinate (x, y, z)
 * is pre-computed.
 *
 */
class Grid
{
public:
    Grid(size_t width, size_t height, size_t depth)
        : m_width(width),
          m_height(height),
          m_depth(depth)
    {
        m_totalCells = width * height * depth;
        m_grid.resize(m_totalCells, 0);
        m_offset = preComputeCellsOffset(m_width, m_height);
    }
    ~Grid() = default;

    size_t getWidth() const { return m_width; }
    size_t getHeight() const { return m_height; }
    size_t getDepth() const { return m_depth; }
    size_t getTotalCells() const { return m_totalCells; }
    uint8_t getCellByPosition(size_t x, size_t y, size_t z) const
    {
        return m_grid[(z * m_height + y) * m_width + x];
    }
    const std::vector<uint8_t> &getGridData() const { return m_grid; };
    const std::array<int, 26> &getOffsets() const { return m_offset; }

private:
    static std::array<int, 26> preComputeCellsOffset(size_t w, size_t h);

private:
    std::vector<uint8_t> m_grid;
    std::array<int, 26> m_offset;
    size_t m_width;      // Grid width (x-dimension).
    size_t m_height;     // Grid height (y-dimension).
    size_t m_depth;      // Grid depth (z-dimension).
    size_t m_totalCells; // Cached total cell count.
};