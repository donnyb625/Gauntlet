#include "pch.h"
#include "../Gauntlet/FileReader.h"
#include "FloorTestAccessor.h"
#include "../Gauntlet/SharedTypes.h"

namespace ConstructorTests
{
	// ########################################################################
	// #                         FILE_READER_TESTS
	// ########################################################################
	TEST(FileReader, RawEntityData)
	{
		FileReader::RawEntityData raw;

		EXPECT_EQ(raw.identification, TileEntity::TileType::NULL_TYPE)
			<< "Initialized with incorrect identification!";
		EXPECT_EQ(raw.x, 0)
			<< "Initialized with incorrect X Position!";
		EXPECT_EQ(raw.y, 0)
			<< "Initialized with incorrect X Position!";
	}
	TEST(FileReader, RawLevelData)
	{
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
	TEST(FileReader, RawPatternData)
	{
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
	TEST(FileReader, FileReader)
	{
		//FileReader reader(std::ifstream(), true);
		// add more tests
	}

	// ########################################################################
	// #                         SHARED_TYPE_TESTS
	// ########################################################################
	namespace SharedTypes
	{
		namespace UsableResource_s
		{
			TEST(Resource, SoundBuffer)
			{
				sf::SoundBuffer buffer;
				UsableResource::Resource sound(&buffer);
			}
			TEST(Resource, Texture)
			{
				sf::Texture texture;
				UsableResource::Resource tex(&texture);
			}
		}
		
		TEST(UsableResource, UsableResource)
		{
			sf::SoundBuffer buffer;
			UsableResource::Resource resource(&buffer);
			UsableResource usable(&resource, 5, ResourceType::GENERIC);
		}
	}
}

namespace FloorTests
{
	// ########################################################################
	// #                         FLOOR_TESTS
	// ########################################################################
	TEST(FloorTest, ConstructorInitializesPropertiesCorrectly) {
    // Define the parameters for the Floor constructor
    int initTotalEntities = 10;
    Entity** initEntities = new Entity*[initTotalEntities];
    int totalPlayers = 2;
    int initTotalTiles = 20;
    TileRegion* initTiles = new TileRegion[initTotalTiles];
    sf::RenderWindow* initWindow = new sf::RenderWindow();
    sf::Color initBG = sf::Color::Black;
    sf::Color initFG = sf::Color::White;
    WallStyle initWallStyle = WallStyle::EXAMPLE_1;
    FloorStyle initFloorStyle = FloorStyle::EXAMPLE_1;

    // Create a Floor object
    Floor floor(initTotalEntities, initEntities, totalPlayers, initTotalTiles, initTiles, initWindow, initBG, initFG, initWallStyle, initFloorStyle);

    // Check that the properties have been initialized correctly using FloorTestAccessor
    EXPECT_EQ(FloorTestAccessor::getTotalEntities(floor), initTotalEntities);
    EXPECT_EQ(FloorTestAccessor::getTotalTiles(floor), initTotalTiles);
    EXPECT_EQ(FloorTestAccessor::getBGColor(floor), initBG);
    EXPECT_EQ(FloorTestAccessor::getFGColor(floor), initFG);
    EXPECT_EQ(FloorTestAccessor::getWallStyle(floor), initWallStyle);
    EXPECT_EQ(FloorTestAccessor::getFloorStyle(floor), initFloorStyle);

    // Clean up
    delete[] initEntities;
    delete[] initTiles;
    delete initWindow;
}

TEST(FloorTest, ConstructorHandlesZeroEntities) {
    // Define the parameters for the Floor constructor
    int initTotalEntities = 0;
    Entity** initEntities = nullptr;
    int totalPlayers = 0;
    int initTotalTiles = 0;
    TileRegion* initTiles = nullptr;
    sf::RenderWindow* initWindow = new sf::RenderWindow();
    sf::Color initBG = sf::Color::Black;
    sf::Color initFG = sf::Color::White;
    WallStyle initWallStyle = WallStyle::EXAMPLE_1;
    FloorStyle initFloorStyle = FloorStyle::EXAMPLE_1;

    // Create a Floor object
    Floor floor(initTotalEntities, initEntities, totalPlayers, initTotalTiles, initTiles, initWindow, initBG, initFG, initWallStyle, initFloorStyle);

    // Check that the properties have been initialized correctly using FloorTestAccessor
    EXPECT_EQ(FloorTestAccessor::getTotalEntities(floor), initTotalEntities);
    EXPECT_EQ(FloorTestAccessor::getTotalTiles(floor), initTotalTiles);
    EXPECT_EQ(FloorTestAccessor::getBGColor(floor), initBG);
    EXPECT_EQ(FloorTestAccessor::getFGColor(floor), initFG);
    EXPECT_EQ(FloorTestAccessor::getWallStyle(floor), initWallStyle);
    EXPECT_EQ(FloorTestAccessor::getFloorStyle(floor), initFloorStyle);

    // Clean up
    delete initWindow;
}
}