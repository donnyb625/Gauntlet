#include "pch.h"
#include "CppUnitTest.h"
#include "gtest/gtest.h"
#include "../Gauntlet/FileReader.h"
#include "../Gauntlet/Tile.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GauntletUnitTests
{
	TEST_CLASS(GauntletUnitTests)
	{
		public:

		// Test construction of RawEntityData
		TEST_METHOD(FileReaderRawEntityConstruction)
		{
			FileReader::RawEntityData raw;

			Assert::AreEqual(
				TileEntity::TileType::NULL_TYPE,
				raw.identification,
				L"Identification did not initialize to NULL_TYPE"
			);
			int i = sizeof(long long);
			Assert::AreEqual(
				0,
				raw.x,
				L"X Position did not initialize to 0"
			);

			Assert::AreEqual(
				0,
				raw.y,
				L"Y Position did not initialize to 0"
			);
		}

		// Test construction of RawPatternData
		TEST_METHOD(FileReaderRawPatternConstruction)
		{
			FileReader::RawPatternData raw;
			unsigned char expected = 0;
			
			for (int i = 0; i < 4; i++)
			{
				Assert::AreEqual(
					expected,
					raw.positionBuffer[i],
					L"Position did not initialize as all 0's"
				);
			}
			
			Assert::AreEqual(
				RegionType::NULL_TYPE,
				raw.patternType,
				L"Pattern type did not initialize as NULL_TYPE"
			);

			for (int i = 0; i < 2; i++)
			{
				Assert::AreEqual(
					Tile::TileType::NULL_TYPE,
					raw.tileIDs[i],
					L"Tile IDs did not initialize to NULL_TYPE"
				);
			}
		}
		
		TEST_METHOD(Tile_ExceptionOnNULL_TYPE)
		{
			Tile tile;

			// Expect a std::runtime_error exception when calling tick()
			Assert::ExpectException<std::runtime_error>(
				[&tile]() { tile.tick(); },
				L"Tile.Tick() did not throw an exception on NULL_TYPE"
			);
		}
	};
}
