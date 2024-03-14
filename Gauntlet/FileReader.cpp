#include "FileReader.h"



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