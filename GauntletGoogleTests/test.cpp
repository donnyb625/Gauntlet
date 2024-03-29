#include "pch.h"
#include "../Gauntlet/FileReader.h"

namespace ConstructorTests
{
	TEST(FileReader, RawEntityData) {
		FileReader::RawEntityData raw;

		EXPECT_EQ(raw.identification, TileEntity::TileType::NULL_TYPE)
			<< "Initialized with incorrect identification!";
		EXPECT_EQ(raw.x, 0)
			<< "Initialized with incorrect X Position!";
		EXPECT_EQ(raw.y, 0)
			<< "Initialized with incorrect X Position!";
	}
	TEST(FileReader, RawLevelData) {
		FileReader::RawLevelData raw;

		EXPECT_EQ(raw.bgColor, sf::Color(0))
			<< "Initialized with incorrect Background Color!";
		EXPECT_EQ(raw.fgColor, sf::Color(0))
			<< "Initialized with incorrect Foreground Color!";
		EXPECT_EQ(raw.entities, nullptr)
			<< "Initialized as not set to nullptr!";
		EXPECT_EQ(raw.patterns, nullptr)
			<< "Initialized as not set to nullptr!";
		EXPECT_EQ(raw.floorStyle, FloorStyle::NULL_STYLE)
			<< "Initialized with incorrect Floor Style!";
		EXPECT_EQ(raw.wallStyle, WallStyle::NULL_STYLE)
			<< "Initialized with incorrect Wall Style!";
		EXPECT_EQ(raw.totalEntities, 0)
			<< "Initialized with incorrect Total Entities!";
		EXPECT_EQ(raw.totalPatterns, 0)
			<< "Initialized with incorrect Total Patterns!";
	}
	TEST(FileReader, RawPatternData) {
		FileReader::RawPatternData raw;

		EXPECT_EQ(raw.patternType, RegionType::NULL_TYPE)
			<< "Initialized with incorrect Pattern Type!";

		for (int i = 0; i < 4; i++)
			EXPECT_EQ(raw.positionBuffer[i], 0)
			<< "Initialized with Garbage Position Buffer!";

		for (int i = 0; i < 2; i++)
			EXPECT_EQ(raw.tileIDs[i], 0)
			<< "Initialized with incorrect Tile IDs!";
	}
	TEST(FileReader, FileReader) {
		//FileReader reader(std::ifstream(), true);
		// add more tests
	}
}