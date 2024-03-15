#include "FileReader.h"
#include "SharedTypes.h"


FileReader::~FileReader()
{
	if (fDat.levelData) {
		for (int i = 0; i < fDat.totalLevels; i++) {
			if (fDat.levelData[i].entities) {
				delete[] fDat.levelData[i].entities;
			}
			if (fDat.levelData[i].patterns) {
				delete[] fDat.levelData[i].patterns;
			}
		}
		delete[] fDat.levelData;
	}
}

/*
  levelfDat.bin Data Structure

  File Header:   ( 1 byte : Total Levels )
  Level Header:  ( 6 byte : Color Scheme   | 1 byte      : Wall Style
		 \-----> | 1 byte : floor Style    | 2 byte      : Pattern Array Size )
  Level Data:    ( 1 byte : Pattern type   | 1 or 2 byte : Tile ID )
  Entity Header: ( 2 byte : Total Entities )
  Entity Data:   ( 1 byte : Entity Type ID | 2 byte      : Position)


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
FileReader::FloorData* FileReader::readLevelData()
{
	int currentLevel = 0, currentPattern = 0, currentEntity = 0;
	int stage = FILE_HEADER_TOTAL_LEVELS;
	/*
		have structs that hold generic data for full types
		have dynamic arrays of levels
		have dynamic arrays of entities
		set array sizes based upon size data stored in file
	*/



	// Runs for every stage, needs to be changed to a different loop
	do
	{
		/*
			This switch statement models stages in file decoding. These stages
			may not happen in the exact order present; IE, it loops over every
			level, and the contained patterns as well as contained entities by
			changing the stage to the start of a level and incrementing a
			counter to note how many it has processed.
		*/
		switch (stage)
		{
		case FILE_HEADER_TOTAL_LEVELS:
			fDat.totalLevels = readData();

			// Initialize the array of level data
			fDat.levelData = new RawLevelData[fDat.totalLevels];
			break;

		case LEVEL_HEADER_BG_COLOR:
			fDat.levelData[currentLevel].bgColor = sf::Color(readColor());
			break;

		case LEVEL_HEADER_FG_COLOR:
			fDat.levelData[currentLevel].fgColor = sf::Color(readColor());
			break;

		case LEVEL_HEADER_WALL_STYLE:
			fDat.levelData[currentLevel].wallStyle =
				static_cast<WallStyle>(readData());
			break;

		case LEVEL_HEADER_FLOOR_STYLE:
			fDat.levelData[currentLevel].floorStyle =
				static_cast<FloorStyle>(readData());
			break;

		case LEVEL_HEADER_TOTAL_PATTERNS:
			fDat.levelData[currentLevel].totalPatterns = readSize();

			//
			fDat.levelData[currentLevel].patterns =
				new RawPatternData[fDat.levelData[currentLevel].totalPatterns];
			break;

		case LEVEL_DATA_PATTERN_TYPE:
			fDat.levelData[currentLevel].patterns[currentPattern].patternType =
				static_cast<RegionType>(readData());
			break;

		case LEVEL_DATA_TILE_ID:
			fDat.levelData[currentLevel].patterns[currentPattern].tileIDs[0] =
				static_cast<Tile::TileType>(readData());

			// Handle these seperately since they require 2 tiles.
			if (
				fDat.levelData[currentLevel].patterns[currentPattern]
				.patternType == RegionType::CHECKERBOARD_TWO_ROW ||
				fDat.levelData[currentLevel].patterns[currentPattern]
				.patternType == RegionType::CHECKERBOARD_TWO_ALTERNATE
				)
			{
				fDat.levelData[currentLevel].patterns[currentPattern]
					.tileIDs[1] = static_cast<Tile::TileType>(readData());
			}
			break;

		case ENTITY_HEADER_TOTAL:
			fDat.levelData[currentLevel].totalEntities = readData();

			// Initialize array for the total entities.
			fDat.levelData[currentLevel].entities =
				new RawEntityData[fDat.levelData[currentLevel].totalEntities];
			break;

		case ENTITY_DATA_TYPE:
			fDat.levelData[currentLevel].entities[currentEntity]
				.identification = static_cast<ResourceIdentifier>(readData());
			break;

		case ENTITY_DATA_X_POS:
			fDat.levelData[currentLevel].entities[currentEntity]
				.x = readData();
			break;

		case ENTITY_DATA_Y_POS:
			fDat.levelData[currentLevel].entities[currentEntity]
				.y = readData();
			break;

		default: 
			throw std::invalid_argument("Invalid read state");
		}


		// Adjust stage depending on if metadata states more present.
		if (stage == LEVEL_DATA_TILE_ID &&
			currentPattern < fDat.levelData[currentLevel].totalPatterns - 1)
		{
			currentPattern++;
			stage = LEVEL_DATA_PATTERN_TYPE;
		}
		else if (stage == ENTITY_DATA_Y_POS &&
			currentEntity < fDat.levelData[currentLevel].totalEntities -1)
		{
			currentEntity++;
			stage = ENTITY_DATA_TYPE;
		}
		else if (stage == ENTITY_DATA_Y_POS &&
			currentLevel < fDat.totalLevels - 1)
		{
			currentLevel++;
			stage = LEVEL_HEADER_BG_COLOR;
		}
	} while (stage != ENTITY_DATA_Y_POS);
}

unsigned char FileReader::readData()
{
	unsigned char result = 0;
	file->read(reinterpret_cast<char*>(&result), 1); // Reading 1 byte
	return result;
}

unsigned short FileReader::readSize()
{
	unsigned char buffer[2];
	file->read(reinterpret_cast<char*>(buffer), 2); // Reading 2 bytes
	return static_cast<unsigned short>((buffer[1] << 8) | buffer[0]);
}

unsigned int FileReader::readColor()
{
	unsigned char buffer[3];
	file->read(reinterpret_cast<char*>(buffer), 3); // Reading 3 bytes

	unsigned int result = buffer[0] | (buffer[1] << 8) | (buffer[2] << 16);
	return result;
}