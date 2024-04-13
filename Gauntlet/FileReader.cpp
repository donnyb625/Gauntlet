#include "FileReader.h"


FileReader::FileReader(std::ifstream& initFile, bool initFiletype)
	: file(&initFile), filetype(initFiletype)
{
	if (filetype)
	{
		floorData.totalLevels = readData();

		floorData.levelData = new RawLevelData[floorData.totalLevels];
	}
}

FileReader::~FileReader()
{
	if (floorData.levelData) {
		for (int i = 0; i < floorData.totalLevels; i++) {
			if (floorData.levelData[i].entities) {
				delete[] floorData.levelData[i].entities;
			}
			if (floorData.levelData[i].patterns) {
				delete[] floorData.levelData[i].patterns;
			}
		}
		delete[] floorData.levelData;
	}
}

/*
  levelfloorData.bin Data Structure

  File Header:   ( 1 byte  : Total Levels )
  Level Header:  ( 6 bytes : Color Scheme   | 1 byte     : Wall Style
		 \-----> | 1 byte  : floor Style    | 2 bytes    : Pattern Array Size )
  Level Data:    ( 1 byte  : Pattern type   | 1/2 bytes  : Tile ID
		 \-----> | 4 bytes : Pattern Array Size )
  Entity Header: ( 2 bytes : Total Entities )
  Entity Data:   ( 1 byte  : Entity Type ID | 2 bytes    : Position)


  The file header holds the number of levels that will actually be present in
  the file. The Level Header holds the specifics like the color schems which is
  what colors the floor and walls will use, first 3 for walls last 3 for floor.
  Then after the color scheme we have the wall and floor styles since they are
  the only two that have varying textures; and lastly we have the number of
  patterns that are contained following the header. These patterns refer to
  tile patterns specifically, and the number of tiles actually required for the
  pattern. The Level Data is an array of patterns and tile IDs so that the
  level can be constructed effectively. After we have the Level Data we will
  have the Entity Header for that specific level. this creates the following
  implicit sub-structure:

  File Header | Level Header | [ Level Data | Entity Header | Entity Data ]

  Where the array of levels also holds the specific entity data for each one as
  well. The Entity Header and Entity Data will hold the number of entities and
  respectively the ID and position of each one.
*/
FileReader::RawLevelData FileReader::readNextLevelData()
{
	int totalPatterns, totalEntities;
	RegionType currentPatternType;


	// Level Header
	floorData.levelData[floorData.currentLevel].bgColor
		= sf::Color(readColor() + 255); // 255 for alpha value
	floorData.levelData[floorData.currentLevel].fgColor
		= sf::Color(readColor() + 255); // 255 for alpha value
	floorData.levelData[floorData.currentLevel].wallStyle
		= static_cast<WallStyle>(readData());
	floorData.levelData[floorData.currentLevel].floorStyle
		= static_cast<FloorStyle>(readData());
	floorData.levelData[floorData.currentLevel].totalPatterns = readSize();
	totalPatterns = floorData.levelData[floorData.currentLevel].totalPatterns;
	floorData.levelData[floorData.currentLevel].patterns
		= new RawPatternData[totalPatterns];

	// Read all pattern data
	for (int i = 0; i < totalPatterns; i++)
	{
		floorData.levelData[floorData.currentLevel].patterns[i].patternType
			= static_cast<RegionType>(readData());
		currentPatternType = floorData.levelData[floorData.currentLevel]
			.patterns[i].patternType;

		floorData.levelData[floorData.currentLevel].patterns[i].tileIDs[0]
			= static_cast<Tile::TileType>(readData());

		// If pattern requires 2 tiles
		if (currentPatternType == RegionType::CHECKERBOARD_TWO_ROW ||
			currentPatternType == RegionType::CHECKERBOARD_TWO_ALTERNATE)
		{
			floorData.levelData[floorData.currentLevel].patterns[i].tileIDs[1]
				= static_cast<Tile::TileType>(readData());
		}

		// Read position from file
		readPosition(floorData.levelData[floorData.currentLevel].patterns[i]
			.positionBuffer);
	}

	floorData.levelData[floorData.currentLevel].totalEntities = readSize();
	totalEntities = floorData.levelData[floorData.currentLevel].totalEntities;
	floorData.levelData[floorData.currentLevel].entities
		= new RawEntityData[totalEntities];

	// Read all entity data
	for (int i = 0; i < totalEntities; i++)
	{
		floorData.levelData[floorData.currentLevel].entities[i].identification
			= static_cast<TileEntity::TileType>(readData());
		floorData.levelData[floorData.currentLevel].entities[i].x
			= readData();
		floorData.levelData[floorData.currentLevel].entities[i].y
			= readData();
	}

	floorData.currentLevel++;
	
	return floorData.levelData[floorData.currentLevel - 1];
}

byte FileReader::readData()
{
	byte result = 0;
	file->read(reinterpret_cast<char*>(&result), 1); // Reading 1 byte
	return result;
}

size FileReader::readSize()
{
	byte buffer[2];
	file->read(reinterpret_cast<char*>(buffer), 2); // Reading 2 bytes
	return static_cast<size>((buffer[1] << 8) | buffer[0]);
}

color FileReader::readColor()
{
	byte buffer[3];
	file->read(reinterpret_cast<char*>(buffer), 3); // Reading 3 bytes

	color result = buffer[0] | (buffer[1] << 8) | (buffer[2] << 16);
	return result;
}

void FileReader::readPosition(byte out[4])
{
	file->read(reinterpret_cast<char*>(out), 4); // Reading 4 bytes
}