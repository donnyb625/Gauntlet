#pragma once
#include "FileReader.h"

class FileEncoder
{
public:
    FileEncoder();
    ~FileEncoder();

    void encodeRawLevelData(FileReader::FloorData& data);
    
private:
    void encodeRawLevelData(FileReader::RawLevelData& data);
    void encodePatterns(FileReader::RawPatternData* patterns, size_t totalPatterns);
    void encodeEntities(FileReader::RawEntityData* entities, size_t totalEntities);
    void encodeColor(sf::Color color);
    void encodeData(byte data);
    void encodeSize(size_t size);
    void encodePosition(byte position[4]);
    void encodeFloorMetadata(FileReader::RawLevelData& data);


    std::fstream* file;
};
