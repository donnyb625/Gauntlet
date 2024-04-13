#include "Patternizer.h"


Patternizer::~Patternizer()
{
}

void Patternizer::patternize(std::set<>)
{
}


void Patternizer::discoverPrimitives(
    std::set<PrimitiveRegion>& points,
    std::set<PrimitiveRegion>& horizontals,
    std::set<PrimitiveRegion>& verticals,
    std::set<PrimitiveRegion>& diagonals,
    Tile::TileType** tiles
    )
{
    // Stores the directions in which a tile has its lengths defined IE how far
    // out it extends in that direction
    uint8_t hasLength[32][32];
    
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            wanderer(points, horizontals, verticals, diagonals, tiles[j][i],
                j, i, tiles, hasLength);
        }
    }
}

void Patternizer::wanderer(
    std::set<PrimitiveRegion>& points,
    std::set<PrimitiveRegion>& horizontals,
    std::set<PrimitiveRegion>& verticals,
    std::set<PrimitiveRegion>& diagonals,
    Tile::TileType& tile, byte x, byte y,
    Tile::TileType** tiles, uint8_t hasLength[32][32]
    )
{
    // Directions: NE/NW/SE/SW/N/S/E/W
    uint8_t hasTraveled = 0b00000000;
    byte lengths[8] = {0, 0, 0, 0, 0, 0, 0, 0}; 
    

    // If not at the top; get northern lengths
    if (y != 0)
    {
        lengths[4] = getLength(0b00001000, hasLength,
            tile, x, y, tiles); // North
        if (x != 0)
            lengths[1] = getLength(0b01000000, hasLength,
                tile, x, y, tiles); // North West
        if (x != 31)
            lengths[0] = getLength(0b10000000, hasLength,
                tile, x, y, tiles); // North East
    }
    hasTraveled |= 0b11001000; // Northern directions

    // If not at the bottom; get southern lengths
    if (y != 31)
    {
        lengths[5] = getLength(0b00000100, hasLength,
            tile, x, y, tiles); // South
        if (x != 0)
            lengths[3] = getLength(0b00010000, hasLength,
                 tile, x, y, tiles); // South West
        if (x != 31)
            lengths[2] = getLength(0b00100000, hasLength,
                 tile, x, y, tiles); // South East
    }
    hasTraveled |= 0b00110100; // Southern directions

    // If not at the east edge; get eastern lengths
    if (x != 0)
        lengths[6] = getLength(0b00000010, hasLength,
            tile, x, y, tiles); // East
    hasTraveled |= 0b00000010; // East

    // If not at the west edge; get western lengths
    if (x != 0)
        lengths[6] = getLength(0b00000010, hasLength,
            tile, x, y, tiles); // West
    hasTraveled |= 0b00000001; // West

    hasLength[y][x] = hasTraveled;
}

byte Patternizer::getLength(const uint8_t direction, uint8_t hasLength[32][32], const Tile::TileType& tile,
    byte x, byte y, Tile::TileType** tiles)
{
    int xOffset = 0, yOffset = 0;
    bool reachedEnd = false;
    byte length = 1;
    uint8_t traveledFlags = 0b00000000;

    // Set offsets based on flags; default is 0 for offsets
    // NE/NW/SE/SW/N/S/E/W
    if ((direction & 0b00000001) == 0b00000001)      // West
    {
        xOffset = -1;
        traveledFlags |= 0b00000011;
    }
    else if ((direction & 0b00000010) == 0b00000010) // East
    {
        xOffset = 1;
        traveledFlags |= 0b00000011;
    }
    else if ((direction & 0b00000100) == 0b00000100) // South
    {
        yOffset = 1;
        traveledFlags |= 0b00001100;
    }
    else if ((direction & 0b00001000) == 0b00001000) // North
    {
        yOffset = -1;
        traveledFlags |= 0b00001100;
    }
    else if ((direction & 0b00010000) == 0b00010000) // South West
    {
        yOffset = 1;
        xOffset = -1;
        traveledFlags |= 0b10010000;
    }
    else if ((direction & 0b00100000) == 0b00100000) // South East
    {
        yOffset = 1;
        xOffset = 1;
        traveledFlags |= 0b01100000;
    }
    else if ((direction & 0b01000000) == 0b01000000) // North West
    {
        yOffset = -1;
        xOffset = -1;
        traveledFlags |= 0b01100000;
    }
    else if ((direction & 0b10000000) == 0b10000000) // North East
    {
        yOffset = -1;
        xOffset = 1;
        traveledFlags |= 0b10010000;
    }

    // While in-bound and unfinished
    while (x + xOffset >= 0 && x + xOffset < 32 &&
           y + yOffset >= 0 && y + yOffset < 32 &&
           !reachedEnd)
    {
        // Check if the next tile in path is the same
        if (tile == tiles[y + yOffset][x + xOffset])
        {
            length++;
            x += xOffset;
            y += yOffset;

            // Make sure is set to traveled in these directions
            hasLength[y][x] |= traveledFlags;
        }
        else // Otherwise stop
            reachedEnd = true;
    }

    return length;
}
