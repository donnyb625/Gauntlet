#pragma once

#include <set>
#include "SharedTypes.h"

class Patternizer
{
public:
    Patterizer();
    ~Patternizer();

    void patternize(std::set<>)
private:
    
    struct PrimitiveRegion
    {
        byte x;
        byte y;
        byte length; // Based at 1 IE a length of 1 means its 1 long
    
        PrimitiveRegion(byte x, byte y, byte length) : x(x), y(y),
            length(length) {};
    };
    
    static void discoverPrimitives(
        std::set<PrimitiveRegion>& points,
        std::set<PrimitiveRegion>& horizontals,
        std::set<PrimitiveRegion>& verticals,
        std::set<PrimitiveRegion>& diagonals,
        Tile::TileType** tiles
        );

    static void wanderer(
        std::set<PrimitiveRegion>& points,
        std::set<PrimitiveRegion>& horizontals,
        std::set<PrimitiveRegion>& verticals,
        std::set<PrimitiveRegion>& diagonals,
        Tile::TileType& tile, byte x, byte y,
        Tile::TileType** tiles, uint8_t hasLength[32][32]
        );

    static byte getLength(uint8_t direction, uint8_t hasLength[32][32], const Tile::TileType& tile,
        byte x, byte y, Tile::TileType** tiles);
};
