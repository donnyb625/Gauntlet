#pragma once
/*
#include <queue>
#include <set>
#include <unordered_map>

#include "SharedTypes.h"

class Patternizer
{
public:
    Patternizer();
    ~Patternizer();

    void patternize(Tile::TileType** tiles);
private:
    struct PrimitiveRegion
    {
        //################################################//
        // Equality operators for comparison in the queue //
        friend bool operator==(const PrimitiveRegion& lhs,
            const PrimitiveRegion& rhs)
        {
            return lhs.x == rhs.x
                && lhs.y == rhs.y
                && lhs.length == rhs.length
                && lhs.flippedDiagonal == rhs.flippedDiagonal
                && lhs.intersectingHorizontals == rhs.intersectingHorizontals
                && lhs.intersectingVerticals == rhs.intersectingVerticals;
        }

        friend bool operator!=(const PrimitiveRegion& lhs,
            const PrimitiveRegion& rhs)
        {
            return !(lhs == rhs);
        }
        //################################################//
        
        byte x, y; // Starting position
        byte length; // Based at 1 IE a length of 1 means it's 1 long.
        bool flippedDiagonal = false;
        byte intersectingHorizontals = 0;
        byte intersectingVerticals = 0;
    
        PrimitiveRegion(byte x, byte y, byte length) : x(x), y(y),
            length(length) {}

        // Constructor for diagonal lines.
        PrimitiveRegion(byte x, byte y, byte length, bool flipped)
            : x(x), y(y), length(length), flippedDiagonal(flipped) {}
    };
    
    struct ComparePreferX {
        bool operator()(const PrimitiveRegion& lhs, const PrimitiveRegion& rhs)
        const {
            if (lhs.x != rhs.x) return lhs.x < rhs.x;
            if (lhs.y != rhs.y) return lhs.y < rhs.y;
            return lhs.length < rhs.length;
        }
    };

    struct ComparePreferY {
        bool operator()(const PrimitiveRegion& lhs, const PrimitiveRegion& rhs)
        const {
            if (lhs.y != rhs.y) return lhs.y < rhs.y;
            if (lhs.x != rhs.x) return lhs.x < rhs.x;
            return lhs.length < rhs.length;
        }
    };
    
    // Wrapper for the wanderer to run at every position
    static void discoverPrimitives(
        std::set<PrimitiveRegion>& points,
        std::set<PrimitiveRegion, ComparePreferY>& horizontals,
        std::set<PrimitiveRegion, ComparePreferX>& verticals,
        std::set<PrimitiveRegion>& diagonals,
        Tile::TileType** tiles
        );

    // Gets all the possible primitives at the point
    static void wanderer(
        std::set<PrimitiveRegion>& points,
        std::set<PrimitiveRegion, ComparePreferY>& horizontals,
        std::set<PrimitiveRegion, ComparePreferX>& verticals,
        std::set<PrimitiveRegion>& diagonals,
        Tile::TileType& tile, byte x, byte y,
        Tile::TileType** tiles, uint8_t hasLength[32][32]
        );

    // Gets the length of a line in a given direction
    static byte getLength(
        uint8_t direction,
        uint8_t hasLength[32][32],
        const Tile::TileType& tile,
        byte x, byte y, Tile::TileType** tiles
        );

    // Updates the sets to hold objects with their intersection counts included
    static void getIntersections(
        std::set<PrimitiveRegion, ComparePreferY>& horizontals,
        std::set<PrimitiveRegion, ComparePreferX>& verticals
        );

    // Applies updates to the horizontal set using the queue
    static void applyUpdatesHorizontal(
        std::set<PrimitiveRegion, ComparePreferY>& regions,
        std::queue<PrimitiveRegion> mappings[2]
        );
    
    // Applies updates to the horizontal set using the queue
    static void applyUpdatesVertical(
        std::set<PrimitiveRegion, ComparePreferX>& regions,
        std::queue<PrimitiveRegion> mappings[2]
        );
    
    // Simple predicate function for line intersection checking
    static bool intersects(
        const PrimitiveRegion& horizontal,
        const PrimitiveRegion& vertical
        );

    // Links the intersections between the horizontal and vertical sets
    static void linkIntersections(
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
    );


    // Returns a set containing all boxes found with that top horizontal
    static std::set<TileRegion>* findBoxes(
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
    );
};
*/