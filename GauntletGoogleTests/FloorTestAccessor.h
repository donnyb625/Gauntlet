#pragma once
#include "../Gauntlet/Floor.h"
#include "../Gauntlet/Entity.h"

class FloorTestAccessor {
public:
    static int getTotalEntities(Floor& floor) {
        return floor.totalEntities;
    }
    
    static Entity** getEntities(Floor& floor) {
        return floor.entities;
    }

    static int getTotalTiles(Floor& floor) {
        return floor.totalTiles;
    }

    static Tile(*getTiles(Floor& floor))[32]
    {
            return floor.tiles;
    }

    static sf::RenderWindow* getWindow(Floor& floor) {
        return floor.window;
    }

    static sf::Color getBGColor(Floor& floor) {
        return floor.bgColor;
    }

    static sf::Color getFGColor(Floor& floor) {
        return floor.fgColor;
    }

    static WallStyle getWallStyle(Floor& floor) {
        return floor.wallStyle;
    }

    static FloorStyle getFloorStyle(Floor& floor) {
        return floor.floorStyle;
    }
};