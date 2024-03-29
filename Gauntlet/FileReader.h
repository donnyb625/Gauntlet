#pragma once
#include <fstream>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include "SharedTypes.h"
#include "TileEntity.h"


// Reads either floor data into memory or reads sprite data for ResourceManager
class FileReader
{
public:
	// Holds the raw pattern information collected from the file for rebuilding
	struct RawPatternData
	{
		unsigned char positionBuffer[4];
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
		unsigned short totalPatterns, totalEntities;

		RawPatternData* patterns;
		RawEntityData* entities;


		RawLevelData()
			: bgColor(), fgColor(), wallStyle(), floorStyle(),
			totalPatterns(0), totalEntities(0), patterns(nullptr),
			entities(nullptr) {}
	};


	FileReader(std::ifstream& initFile, bool filetype);
	~FileReader();

	RawLevelData* readNextLevelData();

private:
	// Holds all the extracted data
	struct FloorData
	{
		unsigned char totalLevels;
		int currentLevel = 0;

		RawLevelData* levelData;


		FloorData() : levelData(nullptr), totalLevels(0) {}
	};

	std::ifstream* file;
	bool filetype;

	FloorData floorData;

	unsigned char readData();
	unsigned short readSize();
	unsigned int readColor();
	void readPosition(unsigned char out[4]);

	
};

