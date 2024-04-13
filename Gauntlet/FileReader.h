#pragma once
#include <fstream>
#include <iostream>
#include "SharedTypes.h"
#include "TileEntity.h"

class FileEncoder;

// Reads either floor data into memory or reads sprite data for ResourceManager
class FileReader
{
public:
	// Holds the raw pattern information collected from the file for rebuilding
	struct RawPatternData
	{
		byte positionBuffer[4];
		RegionType patternType;
		Tile::TileType tileIDs[2];

		RawPatternData() : 
			positionBuffer{0,0,0,0}, patternType(RegionType::NULL_TYPE),
			tileIDs{Tile::TileType::NULL_TYPE,Tile::TileType::NULL_TYPE} {}
	};

	// Holds the raw entity data for placing all default entities
	struct RawEntityData
	{
		TileEntity::TileType identification;
		int x, y;

		RawEntityData() : identification(TileEntity::TileType::NULL_TYPE),
			x(0), y(0) {}
	};

	// Holds the raw data needed for constructing all levels
	struct RawLevelData
	{
		sf::Color bgColor, fgColor;
		WallStyle wallStyle;
		FloorStyle floorStyle;
		size totalPatterns, totalEntities;

		RawPatternData* patterns;
		RawEntityData* entities;


		RawLevelData()
			: bgColor(0), fgColor(0), wallStyle(WallStyle::NULL_STYLE),
			floorStyle(FloorStyle::NULL_STYLE), totalPatterns(0),
			totalEntities(0), patterns(nullptr), entities(nullptr) {}
	};


	FileReader(std::ifstream& initFile, bool filetype);
	~FileReader();

	RawLevelData readNextLevelData();

private:
	// Holds all the extracted data
	struct FloorData
	{
		byte totalLevels;
		int currentLevel = 0;

		RawLevelData* levelData;


		FloorData() : levelData(nullptr), totalLevels(0) {}
	};

	std::ifstream* file;
	bool filetype;

	FloorData floorData;

	byte readData();
	size readSize();
	color readColor();
	void readPosition(byte out[4]);

	
	friend class FileEncoder;
};

