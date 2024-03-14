#include "FileReader.h"
#include "SharedTypes.h"


/*
  levelData.bin Data Structure

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
void FileReader::readLevelData()
{
	unsigned char totalLevels, wallStyle, floorStyle;
	unsigned short patternArraySize;
	sf::Color fgColor, bg_color;
	RegionType patternType;
	Tile::TileType tiles[2];

	/*
		have structs that hold generic data for full types
		have dynamic arrays of levels
		have dynamic arrays of entities
		set array sizes based upon size data stored in file
	*/



	// Runs for every stage, needs to be changed to a different loop
	for (
		int stage = FILE_HEADER_TOTAL_LEVELS; stage < ENTITY_DATA_Y_POS; stage++
		)
	{

		switch (stage)
		{
		case FILE_HEADER_TOTAL_LEVELS:
			break;

		case LEVEL_HEADER_BG_COLOR:
			break;

		case LEVEL_HEADER_FG_COLOR:
			break;

		case LEVEL_HEADER_WALL_STYLE:
			break;

		case LEVEL_HEADER_FLOOR_STYLE:
			break;

		case LEVEL_HEADER_TOTAL_PATTERNS:
			break;

		case LEVEL_DATA_PATTERN_TYPE:
			break;

		case LEVEL_DATA_TILE_ID:
			break;

		case ENTITY_HEADER_TOTAL:
			break;

		case ENTITY_DATA_TYPE:
			break;

		case ENTITY_DATA_X_POS:
			break;

		case ENTITY_DATA_Y_POS:
			break;

		default: 
			throw std::invalid_argument("Invalid read state");
		}
	}
}

unsigned char FileReader::readData(std::ifstream& file)
{
	unsigned char result = 0;
	file.read(reinterpret_cast<char*>(&result), 1); // Reading 1 byte
	return result;
}

unsigned short FileReader::readSize(std::ifstream& file)
{
	unsigned char buffer[2];
	file.read(reinterpret_cast<char*>(buffer), 2); // Reading 2 bytes
	return static_cast<unsigned short>((buffer[1] << 8) | buffer[0]);
}

unsigned int FileReader::readColor(std::ifstream& file)
{
	unsigned char buffer[3];
	file.read(reinterpret_cast<char*>(buffer), 3); // Reading 3 bytes

	unsigned int result = buffer[0] | (buffer[1] << 8) | (buffer[2] << 16);
	return result;
}