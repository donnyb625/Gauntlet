#include "pch.h"
#include "../Gauntlet/SharedTypes.h"
#include "FloorTestAccessor.h"
#include "../Gauntlet/FileReader.h"
#include "../Gauntlet/GameLib.h"
#include "../Gauntlet/Player.h"


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

namespace LibTests
{
	// ########################################################################
	// #                         INPUT_TESTS
	// ########################################################################
	namespace Input
	{
		namespace Keyboard
		{
			sf::Event::KeyEvent event;
	
			TEST(GameLibTest, KeyActionDirection_North) {
				event.code = sf::Keyboard::Up;
				EXPECT_EQ(GameLib::getKeyActionDirection(event), Action::NORTH);
				event.code = sf::Keyboard::W;
				EXPECT_EQ(GameLib::getKeyActionDirection(event), Action::NORTH);
			}

			TEST(GameLibTest, KeyActionDirection_South) {
				event.code = sf::Keyboard::Down;
				EXPECT_EQ(GameLib::getKeyActionDirection(event), Action::SOUTH);
				event.code = sf::Keyboard::S;
				EXPECT_EQ(GameLib::getKeyActionDirection(event), Action::SOUTH);
			}

			TEST(GameLibTest, KeyActionDirection_East) {
				event.code = sf::Keyboard::Right;
				EXPECT_EQ(GameLib::getKeyActionDirection(event), Action::EAST);
				event.code = sf::Keyboard::D;
				EXPECT_EQ(GameLib::getKeyActionDirection(event), Action::EAST);
			}

			TEST(GameLibTest, KeyActionDirection_West) {
				event.code = sf::Keyboard::Left;
				EXPECT_EQ(GameLib::getKeyActionDirection(event), Action::WEST);
				event.code = sf::Keyboard::A;
				EXPECT_EQ(GameLib::getKeyActionDirection(event), Action::WEST);
			}

			TEST(GameLibTest, KeyActionDirection_Shoot) {
				event.code = sf::Keyboard::L;
				EXPECT_EQ(GameLib::getKeyActionDirection(event), Action::SHOOT);
				event.code = sf::Keyboard::Space;
				EXPECT_EQ(GameLib::getKeyActionDirection(event), Action::SHOOT);
			}
		}
	}
}




namespace PlayerTests
{

	//Player Initial Stat Tests
	TEST(Player, WarriorStatsTest)
	{
		Player::PlayerStats warrior = Player::createInitialStats(Player::PlayerType::WARRIOR);
		EXPECT_EQ(warrior.healthPoints, 980);
		EXPECT_EQ(warrior.armor, 4);
		EXPECT_EQ(warrior.attackDamage, 5);
		EXPECT_EQ(warrior.healthGain, 80);
		EXPECT_EQ(warrior.shotSpeed, 0);
		EXPECT_EQ(warrior.magic, 1);
		EXPECT_EQ(warrior.speed, 2);
	}
	TEST(Player, ElfStatsTest)
	{
		Player::PlayerStats elf = Player::createInitialStats(Player::PlayerType::ELF);
		EXPECT_EQ(elf.healthPoints, 820);
		EXPECT_EQ(elf.armor, 2);
		EXPECT_EQ(elf.attackDamage, 2);
		EXPECT_EQ(elf.healthGain, 120);
		EXPECT_EQ(elf.shotSpeed, 0);
		EXPECT_EQ(elf.magic, 3);
		EXPECT_EQ(elf.speed, 5);
	}
	TEST(Player, WizardStatsTest)
	{
		Player::PlayerStats wizard = Player::createInitialStats(Player::PlayerType::WIZARD);
		EXPECT_EQ(wizard.healthPoints, 800);
		EXPECT_EQ(wizard.armor, 1);
		EXPECT_EQ(wizard.attackDamage, 3);
		EXPECT_EQ(wizard.healthGain, 100);
		EXPECT_EQ(wizard.shotSpeed, 0);
		EXPECT_EQ(wizard.magic, 5);
		EXPECT_EQ(wizard.speed, 3);
	}
	TEST(Player, ValkyrieStatsTest)
	{
		Player::PlayerStats valkyrie = Player::createInitialStats(Player::PlayerType::VALKYRIE);
		EXPECT_EQ(valkyrie.healthPoints, 900);
		EXPECT_EQ(valkyrie.armor, 5);
		EXPECT_EQ(valkyrie.attackDamage, 3);
		EXPECT_EQ(valkyrie.healthGain, 100);
		EXPECT_EQ(valkyrie.shotSpeed, 0);
		EXPECT_EQ(valkyrie.magic, 2);
		EXPECT_EQ(valkyrie.speed, 3);
	}

}