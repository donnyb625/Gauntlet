#include "FileEncoder.h"

FileEncoder::FileEncoder()
{
}

FileEncoder::~FileEncoder()
{
}

void FileEncoder::encodeRawLevelData(FileReader::FloorData& data)
{
    encodeSize(data.size);
    encodeFloorMetadata(data.levelData);
    encodePatterns(data.patterns, data.size);
    encodeEntities(data.entities, data.size);
}