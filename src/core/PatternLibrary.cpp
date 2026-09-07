// src/core/PatternLibrary.cpp
#include "PatternLibrary.h"
#include "Utils.h"
#include <random>
#include <cmath>

// ============================================================
// PATTERN 1: BLINKER 3D (Oscillatore classico 2D su un piano)
// ============================================================
void PatternLibrary::initBlinker3D(Grid &grid)
{
    grid.resetGrid();
    const int cx = grid.getWidth() / 2;
    const int cy = grid.getHeight() / 2;
    const int cz = grid.getDepth() / 2;

    // Blinker classico: 3 celle in linea (orizzontale)
    // Oscilla tra orizzontale e verticale
    grid.setCellByPosition(cx - 1, cy, cz, 1);
    grid.setCellByPosition(cx, cy, cz, 1);
    grid.setCellByPosition(cx + 1, cy, cz, 1);
}

// ============================================================
// PATTERN 2: GLIDER 3D (Glider classico su un piano Z)
// ============================================================
void PatternLibrary::initGlider3D(Grid &grid)
{
    grid.resetGrid();
    const int cx = grid.getWidth() / 2;
    const int cy = grid.getHeight() / 2;
    const int cz = grid.getDepth() / 2;

    // Glider classico 2D (si muove in diagonale)
    // . O .
    // . . O
    // O O O
    grid.setCellByPosition(cx, cy, cz, 1);
    grid.setCellByPosition(cx + 1, cy + 1, cz, 1);
    grid.setCellByPosition(cx, cy + 2, cz, 1);
    grid.setCellByPosition(cx + 1, cy + 2, cz, 1);
    grid.setCellByPosition(cx + 2, cy + 2, cz, 1);
}

// ============================================================
// PATTERN 3: GLIDER SU 3 PIANI (Glider 3D che si muove in 3D)
// ============================================================
void PatternLibrary::initGlider3D_Thick(Grid &grid)
{
    grid.resetGrid();
    const int cx = grid.getWidth() / 2;
    const int cy = grid.getHeight() / 2;
    const int cz = grid.getDepth() / 2;

    // Glider classico copiato su 3 piani Z (si muove in 3D)
    for (int dz = -1; dz <= 1; dz++)
    {
        grid.setCellByPosition(cx, cy, cz + dz, 1);
        grid.setCellByPosition(cx + 1, cy + 1, cz + dz, 1);
        grid.setCellByPosition(cx, cy + 2, cz + dz, 1);
        grid.setCellByPosition(cx + 1, cy + 2, cz + dz, 1);
        grid.setCellByPosition(cx + 2, cy + 2, cz + dz, 1);
    }
}

// ============================================================
// PATTERN 4: PULSAR 3D (Oscillatore stabile)
// ============================================================
void PatternLibrary::initPulsar3D(Grid &grid)
{
    grid.resetGrid();
    const int cx = grid.getWidth() / 2;
    const int cy = grid.getHeight() / 2;
    const int cz = grid.getDepth() / 2;

    // Pulsar 2D classico su un piano Z
    // (pattern a croce che pulsa)
    for (int i = -2; i <= 2; i++)
    {
        // Linee orizzontali
        if (i == -2 || i == 2)
        {
            for (int j = -1; j <= 1; j++)
            {
                grid.setCellByPosition(cx + i, cy + j, cz, 1);
            }
        }
        // Linee verticali
        if (i == -1 || i == 1)
        {
            for (int j = -2; j <= 2; j += 4)
            {
                grid.setCellByPosition(cx + i, cy + j, cz, 1);
            }
        }
    }
}

// ============================================================
// PATTERN 5: CUBO 3x3x3 (Stabile con B3/S23)
// ============================================================
void PatternLibrary::initCube3x3x3(Grid &grid)
{
    grid.resetGrid();
    const int cx = grid.getWidth() / 2;
    const int cy = grid.getHeight() / 2;
    const int cz = grid.getDepth() / 2;

    // Cubo 3x3x3 pieno
    for (int dz = -1; dz <= 1; dz++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            for (int dx = -1; dx <= 1; dx++)
            {
                grid.setCellByPosition(cx + dx, cy + dy, cz + dz, 1);
            }
        }
    }
}

// ============================================================
// PATTERN 6: CUBO CAVO (Superficie di un cubo 3x3x3)
// ============================================================
void PatternLibrary::initHollowCube(Grid &grid)
{
    grid.resetGrid();
    const int cx = grid.getWidth() / 2;
    const int cy = grid.getHeight() / 2;
    const int cz = grid.getDepth() / 2;

    // Solo superficie del cubo 3x3x3
    for (int dz = -1; dz <= 1; dz++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            for (int dx = -1; dx <= 1; dx++)
            {
                // Almeno una coordinata è al bordo
                if (abs(dx) == 1 || abs(dy) == 1 || abs(dz) == 1)
                {
                    grid.setCellByPosition(cx + dx, cy + dy, cz + dz, 1);
                }
            }
        }
    }
}

// ============================================================
// PATTERN 7: SFERA (Piena o cava)
// ============================================================
void PatternLibrary::initSphere(Grid &grid)
{
    grid.resetGrid();
    const int cx = grid.getWidth() / 2;
    const int cy = grid.getHeight() / 2;
    const int cz = grid.getDepth() / 2;
    const int radius = std::min({grid.getWidth(),
                                 grid.getHeight(),
                                 grid.getDepth()}) /
                       3;

    // Sfera piena
    for (int dz = -radius; dz <= radius; dz++)
    {
        for (int dy = -radius; dy <= radius; dy++)
        {
            for (int dx = -radius; dx <= radius; dx++)
            {
                float dist = sqrtf(dx * dx + dy * dy + dz * dz);
                if (dist <= radius)
                {
                    grid.setCellByPosition(cx + dx, cy + dy, cz + dz, 1);
                }
            }
        }
    }
}

// ============================================================
// PATTERN 8: SFERA CAVA
// ============================================================
void PatternLibrary::initHollowSphere(Grid &grid)
{
    grid.resetGrid();
    const int cx = grid.getWidth() / 2;
    const int cy = grid.getHeight() / 2;
    const int cz = grid.getDepth() / 2;
    const int radius = std::min({grid.getWidth(),
                                 grid.getHeight(),
                                 grid.getDepth()}) /
                       3;

    // Sfera cava (solo superficie)
    for (int dz = -radius; dz <= radius; dz++)
    {
        for (int dy = -radius; dy <= radius; dy++)
        {
            for (int dx = -radius; dx <= radius; dx++)
            {
                float dist = sqrtf(dx * dx + dy * dy + dz * dz);
                if (dist >= radius - 0.5f && dist <= radius + 0.5f)
                {
                    grid.setCellByPosition(cx + dx, cy + dy, cz + dz, 1);
                }
            }
        }
    }
}

// ============================================================
// PATTERN 9: CROCE 3D (Stabile con B3/S23? - da testare)
// ============================================================
void PatternLibrary::initCross3D(Grid &grid)
{
    grid.resetGrid();
    const int cx = grid.getWidth() / 2;
    const int cy = grid.getHeight() / 2;
    const int cz = grid.getDepth() / 2;
    const int size = std::min({grid.getWidth(),
                               grid.getHeight(),
                               grid.getDepth()}) /
                     4;

    // Asse X
    for (int dx = -size; dx <= size; dx++)
    {
        grid.setCellByPosition(cx + dx, cy, cz, 1);
    }
    // Asse Y
    for (int dy = -size; dy <= size; dy++)
    {
        grid.setCellByPosition(cx, cy + dy, cz, 1);
    }
    // Asse Z
    for (int dz = -size; dz <= size; dz++)
    {
        grid.setCellByPosition(cx, cy, cz + dz, 1);
    }
}

// ============================================================
// PATTERN 10: CAOS (Densità variabile)
// ============================================================
void PatternLibrary::initChaos(Grid &grid, float density)
{
    grid.resetGrid();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    const size_t w = grid.getWidth();
    const size_t h = grid.getHeight();
    const size_t d = grid.getDepth();

    for (size_t z = 0; z < d; z++)
    {
        for (size_t y = 0; y < h; y++)
        {
            for (size_t x = 0; x < w; x++)
            {
                if (dist(gen) < density)
                {
                    grid.setCellByPosition(x, y, z, 1);
                }
            }
        }
    }
}

// ============================================================
// PATTERN 11: ACORN (Pattern 2D che cresce in 3D)
// ============================================================
void PatternLibrary::initAcorn(Grid &grid)
{
    grid.resetGrid();
    const int cx = grid.getWidth() / 2;
    const int cy = grid.getHeight() / 2;
    const int cz = grid.getDepth() / 2;

    // Acorn (pattern che cresce)
    grid.setCellByPosition(cx + 1, cy, cz, 1);
    grid.setCellByPosition(cx + 3, cy + 1, cz, 1);
    grid.setCellByPosition(cx, cy + 2, cz, 1);
    grid.setCellByPosition(cx + 1, cy + 2, cz, 1);
    grid.setCellByPosition(cx + 4, cy + 2, cz, 1);
    grid.setCellByPosition(cx + 5, cy + 2, cz, 1);
    grid.setCellByPosition(cx + 6, cy + 2, cz, 1);
}

// ============================================================
// PATTERN 12: DUE BLINKER INTERAGENTI
// ============================================================
void PatternLibrary::initDoubleBlinker(Grid &grid)
{
    grid.resetGrid();
    const int cx = grid.getWidth() / 2;
    const int cy = grid.getHeight() / 2;
    const int cz = grid.getDepth() / 2;

    // Blinker orizzontale (X)
    grid.setCellByPosition(cx - 1, cy, cz, 1);
    grid.setCellByPosition(cx, cy, cz, 1);
    grid.setCellByPosition(cx + 1, cy, cz, 1);

    // Blinker verticale (Y) a distanza
    grid.setCellByPosition(cx, cy - 1, cz + 2, 1);
    grid.setCellByPosition(cx, cy, cz + 2, 1);
    grid.setCellByPosition(cx, cy + 1, cz + 2, 1);
}

// ============================================================
// PATTERN 13: PIANO DI BLINKER ALTERNATI
// ============================================================
void PatternLibrary::initBlinkerPlane(Grid &grid)
{
    grid.resetGrid();
    const int cx = grid.getWidth() / 2;
    const int cy = grid.getHeight() / 2;
    const int cz = grid.getDepth() / 2;

    // Piano 5x5 di Blinker alternati
    for (int x = -2; x <= 2; x++)
    {
        for (int y = -2; y <= 2; y++)
        {
            if ((x + y) % 2 == 0)
            {
                // Orizzontale (X)
                grid.setCellByPosition(cx + x - 1, cy + y, cz, 1);
                grid.setCellByPosition(cx + x, cy + y, cz, 1);
                grid.setCellByPosition(cx + x + 1, cy + y, cz, 1);
            }
            else
            {
                // Verticale (Y)
                grid.setCellByPosition(cx + x, cy + y - 1, cz, 1);
                grid.setCellByPosition(cx + x, cy + y, cz, 1);
                grid.setCellByPosition(cx + x, cy + y + 1, cz, 1);
            }
        }
    }
}

// ============================================================
// PATTERN DISPATCHER
// ============================================================
void PatternLibrary::initPattern(Grid &grid, Pattern pattern)
{
    switch (pattern)
    {
    case Pattern::BLINKER_3D:
        initBlinker3D(grid);
        break;
    case Pattern::GLIDER_3D:
        initGlider3D(grid);
        break;
    case Pattern::GLIDER_3D_THICK:
        initGlider3D_Thick(grid);
        break;
    case Pattern::PULSAR_3D:
        initPulsar3D(grid);
        break;
    case Pattern::CUBE_3X3X3:
        initCube3x3x3(grid);
        break;
    case Pattern::HOLLOW_CUBE:
        initHollowCube(grid);
        break;
    case Pattern::SPHERE:
        initSphere(grid);
        break;
    case Pattern::HOLLOW_SPHERE:
        initHollowSphere(grid);
        break;
    case Pattern::CROSS_3D:
        initCross3D(grid);
        break;
    case Pattern::ACORN:
        initAcorn(grid);
        break;
    case Pattern::DOUBLE_BLINKER:
        initDoubleBlinker(grid);
        break;
    case Pattern::BLINKER_PLANE:
        initBlinkerPlane(grid);
        break;
    case Pattern::CHAOS:
        initChaos(grid, 0.3f);
        break;
    case Pattern::CHAOS_DENSE:
        initChaos(grid, 0.45f);
        break;
    case Pattern::CHAOS_SPARSE:
        initChaos(grid, 0.15f);
        break;
    case Pattern::EMPTY:
        grid.resetGrid();
        break;
    }
}

// ============================================================
// PATTERN NAME LOOKUP
// ============================================================
const char *PatternLibrary::getPatternName(Pattern pattern)
{
    switch (pattern)
    {
    case Pattern::BLINKER_3D:
        return "Blinker 3D";
    case Pattern::GLIDER_3D:
        return "Glider 3D";
    case Pattern::GLIDER_3D_THICK:
        return "Glider 3D (Thick)";
    case Pattern::PULSAR_3D:
        return "Pulsar 3D";
    case Pattern::CUBE_3X3X3:
        return "Cube 3x3x3";
    case Pattern::HOLLOW_CUBE:
        return "Hollow Cube";
    case Pattern::SPHERE:
        return "Sphere";
    case Pattern::HOLLOW_SPHERE:
        return "Hollow Sphere";
    case Pattern::CROSS_3D:
        return "Cross 3D";
    case Pattern::ACORN:
        return "Acorn";
    case Pattern::DOUBLE_BLINKER:
        return "Double Blinker";
    case Pattern::BLINKER_PLANE:
        return "Blinker Plane";
    case Pattern::CHAOS:
        return "Chaos (30%)";
    case Pattern::CHAOS_DENSE:
        return "Chaos (45%)";
    case Pattern::CHAOS_SPARSE:
        return "Chaos (15%)";
    case Pattern::EMPTY:
        return "Empty";
    default:
        return "Unknown";
    }
}