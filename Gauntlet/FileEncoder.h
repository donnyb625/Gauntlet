#pragma once

#include "FileReader.h"


class FileEncoder
{
public:
	// Construct with fstream
	FileEncoder();

	// update level method, takes an unsigned char for the level num

private:
	// store pointer to stream

	FileReader::FloorData floorData;

	// method to write file
	// static method for converting tiles to patterns -- transform method
};

