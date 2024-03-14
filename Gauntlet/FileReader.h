#pragma once
#include <fstream>
#include <iostream>


class FileReader
{
public:
	FileReader(std::ifstream& initFile) : file(&initFile) {}

private:
	std::ifstream* file;

	void readLevelData();

	unsigned char readData(std::ifstream& file);
	unsigned short readSize(std::ifstream& file);
	unsigned int readColor(std::ifstream& file);
};

