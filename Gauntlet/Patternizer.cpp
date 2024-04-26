#include "Patternizer.h"

#include <iostream>


Patternizer::~Patternizer()
{
}

void Patternizer::patternize(Tile::TileType** tiles)
{
    std::set<PrimitiveRegion> points, diagonals;
    // The comparison functions ensure that linking will produce
    // consecutive intersections for horizontals and verticals.
    std::set<PrimitiveRegion, ComparePreferX> verticals;
    std::set<PrimitiveRegion, ComparePreferY> horizontals;
    std::set<TileRegion> regions;

    // Lookup table for primitive intersections
    std::unordered_map<PrimitiveRegion,std::vector<const PrimitiveRegion*>>
        horizontalIntersections, verticalIntersections;

    
    discoverPrimitives(points, horizontals, verticals, diagonals, tiles);
    linkIntersections(horizontals, verticals,
        horizontalIntersections,verticalIntersections);
    
    // Discover Boxes

    // For every horizontal line with 2 or more intersections
    for (const PrimitiveRegion& horizontal : horizontals)
    {
        if (horizontal.intersectingVerticals >= 2)
        {
            try {
                findBoxes(horizontals, verticals,
                    horizontalIntersections.at(horizontal),
                    verticalIntersections, tiles);
            } catch (const std::out_of_range& e) {
                // Handle the case where the horizontal is not found in the map
                std::cerr <<
                    "No intersections found for the given horizontal region: "
                     << e.what() << std::endl;
            }
        }
    }
}


void Patternizer::discoverPrimitives(
    std::set<PrimitiveRegion>& points,
    std::set<PrimitiveRegion, ComparePreferY>& horizontals,
    std::set<PrimitiveRegion, ComparePreferX>& verticals,
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
    std::set<PrimitiveRegion, ComparePreferY>& horizontals,
    std::set<PrimitiveRegion, ComparePreferX>& verticals,
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
        if ((hasLength[y][x] & 0b00001000) == 0b00001000)
            lengths[4] = getLength(0b00001000, hasLength,
                tile, x, y, tiles); // North
        
        if (x != 0 && (hasLength[y][x] & 0b01000000) == 0b01000000)
            lengths[1] = getLength(0b01000000, hasLength,
                tile, x, y, tiles); // North West
        
        if (x != 31 && (hasLength[y][x] & 0b10000000) == 0b10000000)
            lengths[0] = getLength(0b10000000, hasLength,
                tile, x, y, tiles); // North East
    }

    // If not at the bottom; get southern lengths
    if (y != 31)
    {
        if ((hasLength[y][x] & 0b00000100) == 0b00000100)
            lengths[5] = getLength(0b00000100, hasLength,
                tile, x, y, tiles); // South
        
        if (x != 0 && (hasLength[y][x] & 0b00010000) == 0b00010000)
            lengths[3] = getLength(0b00010000, hasLength,
                 tile, x, y, tiles); // South West
        
        if (x != 31 && (hasLength[y][x] & 0b00100000) == 0b00100000)
            lengths[2] = getLength(0b00100000, hasLength,
                 tile, x, y, tiles); // South East
    }

    // If not at the east edge; get eastern lengths
    if (x != 31 && (hasLength[y][x] & 0b00000010) != 0b00000010)
        lengths[6] = getLength(0b00000010, hasLength,
            tile, x, y, tiles); // East
    

    // If not at the west edge; get western lengths
    if (x != 0 && (hasLength[y][x] & 0b00000001) != 0b00000001)
        lengths[7] = getLength(0b00000001, hasLength,
            tile, x, y, tiles); // West
    
    hasTraveled |= 0b11111111; // Set all direction flags.

    hasLength[y][x] = hasTraveled;

    if (lengths[0] + lengths[3] > 2)
        diagonals.insert(PrimitiveRegion(
            x - lengths[0] + 1, // Get the starting point of the line
            y - lengths[0] + 1,
            lengths[0] + lengths[3] - 1, // Get the length of the line
            true
            ));
    
    if (lengths[1] + lengths[2] > 2)
        diagonals.insert(PrimitiveRegion(
            x - lengths[1] + 1, // Get the starting point of the line
            y - lengths[1] + 1,
            lengths[1] + lengths[2] - 1, // Get the length of the line
            false
            ));
    
    if (lengths[4] + lengths[5] > 2)
        verticals.insert(PrimitiveRegion(
            x + lengths[4] + 1, // Get the starting point of the line
            y + lengths[4] + 1,
            lengths[4] + lengths[5] - 1 // Get the length of the line
            ));
    
    if (lengths[6] + lengths[7] > 2)
        horizontals.insert(PrimitiveRegion(
            x + lengths[7] + 1, // Get the starting point of the line
            y + lengths[7] + 1,
            lengths[6] + lengths[7] - 1 // Get the length of the line
            ));

    if (lengths[0] + lengths[1] + lengths[2] + lengths[3] +
        lengths[4] + lengths[5] + lengths[6] + lengths[7] == 8) // If a point
        points.insert(PrimitiveRegion(x, y, 1));

}

byte Patternizer::getLength(
    const uint8_t direction,
    uint8_t hasLength[32][32],
    const Tile::TileType& tile,
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
        traveledFlags |= 0b00000001;
    }
    else if ((direction & 0b00000010) == 0b00000010) // East
    {
        xOffset = 1;
        traveledFlags |= 0b00000010;
    }
    else if ((direction & 0b00000100) == 0b00000100) // South
    {
        yOffset = 1;
        traveledFlags |= 0b00000100;
    }
    else if ((direction & 0b00001000) == 0b00001000) // North
    {
        yOffset = -1;
        traveledFlags |= 0b00001000;
    }
    else if ((direction & 0b00010000) == 0b00010000) // South West
    {
        yOffset = 1;
        xOffset = -1;
        traveledFlags |= 0b00010000;
    }
    else if ((direction & 0b00100000) == 0b00100000) // South East
    {
        yOffset = 1;
        xOffset = 1;
        traveledFlags |= 0b00100000;
    }
    else if ((direction & 0b01000000) == 0b01000000) // North West
    {
        yOffset = -1;
        xOffset = -1;
        traveledFlags |= 0b01000000;
    }
    else if ((direction & 0b10000000) == 0b10000000) // North East
    {
        yOffset = -1;
        xOffset = 1;
        traveledFlags |= 0b10000000;
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

void Patternizer::getIntersections(
    std::set<PrimitiveRegion, ComparePreferY>& horizontals,
    std::set<PrimitiveRegion, ComparePreferX>& verticals
    )
{
    std::queue<PrimitiveRegion> newHorizontalMappings[2], newVerticalMappings[2];

    // Calculate new intersection counts
    for (const PrimitiveRegion& horizontal : horizontals)
    {
        PrimitiveRegion newHorizontal = horizontal;

        for (const PrimitiveRegion& vertical : verticals)
        {
            if (intersects(horizontal, vertical))
            {
                newHorizontal.intersectingVerticals++;
                // Check if this vertical has been updated already
                if (newVerticalMappings[0].empty() ||
                    newVerticalMappings[0].back() != vertical)
                {
                    newVerticalMappings[0].push(vertical);
                    newVerticalMappings[1].push(vertical);
                }
                newVerticalMappings[1].back().intersectingHorizontals++;
            }
        }
        
        // Apply updates to verticals
        applyUpdatesVertical(verticals, newVerticalMappings);

        if (newHorizontal.intersectingVerticals != horizontal.intersectingVerticals)
        {
            newHorizontalMappings[0].push(horizontal);
            newHorizontalMappings[1].push(newHorizontal);
        }
    }

    // Apply updates to horizontals
    applyUpdatesHorizontal(horizontals, newHorizontalMappings);
}

void Patternizer::applyUpdatesHorizontal(
    std::set<PrimitiveRegion, ComparePreferY>& regions,
    std::queue<PrimitiveRegion> mappings[2]
    )
{
    while (!mappings[0].empty()) {
        regions.erase(mappings[0].front());
        regions.insert(mappings[1].front());
        mappings[0].pop();
        mappings[1].pop();
    }
}
void Patternizer::applyUpdatesVertical(
    std::set<PrimitiveRegion, ComparePreferX>& regions,
    std::queue<PrimitiveRegion> mappings[2]
    )
{
    while (!mappings[0].empty()) {
        regions.erase(mappings[0].front());
        regions.insert(mappings[1].front());
        mappings[0].pop();
        mappings[1].pop();
    }
}

bool Patternizer::intersects(
    const PrimitiveRegion& horizontal,
    const PrimitiveRegion& vertical
    )
{
    return vertical.x >= horizontal.x && vertical.y <= horizontal.y &&
        vertical.x <= horizontal.x + horizontal.length;

}

void Patternizer::linkIntersections(
    const std::set<PrimitiveRegion, ComparePreferY>& horizontals,
    const std::set<PrimitiveRegion, ComparePreferX>& verticals,
    std::unordered_map<
        PrimitiveRegion,
        std::vector<
            const PrimitiveRegion*
    >>& horizontalIntersections,
    std::unordered_map<
        PrimitiveRegion,
        std::vector<
            const PrimitiveRegion*
    >>& verticalIntersections
    )
{
    for (const PrimitiveRegion& horizontal : horizontals)
    {
        for (const PrimitiveRegion& vertical : verticals)
        {
            if (intersects(horizontal, vertical))
            {
                horizontalIntersections[horizontal].push_back(&vertical);
                verticalIntersections[vertical].push_back(&horizontal);
            }
        }
    }
}

std::set<TileRegion>* Patternizer::findBoxes(
    const std::set<PrimitiveRegion, ComparePreferY>& horizontals,
    const std::set<PrimitiveRegion, ComparePreferX>& verticals,
    const PrimitiveRegion& selectedHorizontal,
    const std::unordered_map<
        PrimitiveRegion,
        std::vector<
            const PrimitiveRegion*
            >>& verticalIntersections,
    const std::unordered_map<
        PrimitiveRegion,
        std::vector<
            const PrimitiveRegion*
    >>& horizontalIntersections,
    Tile::TileType** tiles
    )
{
    // NEEDS TO CHECK TILE TYPE
    const std::vector<const PrimitiveRegion*>* verticalsToCheck
        = &horizontalIntersections.at(selectedHorizontal);
    std::vector<const PrimitiveRegion*> legs, feet;

    // Identify legs and feet
    for (PrimitiveRegion vertical : verticalsToCheck) // Ignore last
    {
        if (vertical.intersectingHorizontals >= 2)
        {
            for (const PrimitiveRegion* horizontal
                : verticalIntersections.at(vertical))
            {
                // If this horizontal is below the selected horizontal and
                // leaves at least one layer in between, form a box
                if (horizontal->y < selectedHorizontal.y - 1)
                {
                    legs.push_back(&vertical);
                    feet.push_back(horizontal);
                }
            }
        }
    }

    // 
}
