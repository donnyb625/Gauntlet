#pragma once
#include <fstream>
#include <iostream>


class FileReader
{
public:
	FileReader(std::ifstream& initFile) : file(&initFile) {}

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

	void readLevelData();

	unsigned char readData(std::ifstream& file);
	unsigned short readSize(std::ifstream& file);
	unsigned int readColor(std::ifstream& file);
};

