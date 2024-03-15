#pragma once
#include <fstream>
#include <iostream>


class FileReader
{
public:
	// Holds the raw pattern information collected from the file for rebuilding
	struct RawPatternData
	{
		RegionType patternType;
		Tile::TileType tileIDs[2];

		RawPatternData() : patternType(), tileIDs() {}
	};

	// Holds the raw entity data for placing all default entities
	struct RawEntityData
	{
		ResourceIdentifier identification;
		int x, y;

		RawEntityData() : identification(), x(0), y(0) {}
	};

	// Holds the raw data needed for constructing all levels
	struct RawLevelData
	{
		sf::Color bgColor, fgColor;
		WallStyle wallStyle;
		FloorStyle floorStyle;
		unsigned short totalPatterns, totalEntities;

		RawPatternData* patterns;
		RawEntityData* entities;


		RawLevelData()
			: bgColor(), fgColor(), wallStyle(), floorStyle(),
			totalPatterns(0), totalEntities(0), patterns(nullptr),
			entities(nullptr) {}
	};

	// Holds all the extracted data
	struct FloorData
	{
		unsigned char totalLevels;

		RawLevelData* levelData;


		FloorData() : levelData(nullptr), totalLevels(0) {}
	};

	FileReader(std::ifstream& initFile) : file(&initFile) {}
	~FileReader();

	FloorData* readLevelData();

private:
	enum LevelDataReadStage
	{
		FILE_HEADER_TOTAL_LEVELS,
		LEVEL_HEADER_BG_COLOR,
		LEVEL_HEADER_FG_COLOR,
		LEVEL_HEADER_WALL_STYLE,
		LEVEL_HEADER_FLOOR_STYLE,
		LEVEL_HEADER_TOTAL_PATTERNS,
		LEVEL_DATA_PATTERN_TYPE,
		LEVEL_DATA_TILE_ID,
		ENTITY_HEADER_TOTAL,
		ENTITY_DATA_TYPE,
		ENTITY_DATA_X_POS,
		ENTITY_DATA_Y_POS,

	};

	std::ifstream* file;

	FloorData fDat;

	unsigned char readData();
	unsigned short readSize();
	unsigned int readColor();
};

