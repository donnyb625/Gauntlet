#include "ImageExtractor.h"
#include <vector>

ImageExtractor::ImageExtractor(std::string initPath) : filepath(initPath)
{
	sf::Image image;

	if (!image.loadFromFile(filepath))
		throw std::invalid_argument("Invalid image Path");
}

void ImageExtractor::setReadRegionStart(int x, int y)
{
	readRegionPosStart = sf::Vector2i(x, y);
}

void ImageExtractor::setReadRegionEnd(int x, int y)
{
	readRegionPosEnd = sf::Vector2i(x, y);
}

void ImageExtractor::setInternalDimensions(int width, int height)
{
	internalSectionDimensions = sf::Vector2i(width, height);
}

void ImageExtractor::setInternalHorizOffset(int val)
{
	internalHorizontalOffset = val;
}

void ImageExtractor::setInternalVertOffset(int val)
{
	internalVerticalOffset = val;
}

bool ImageExtractor::extractImages()
{
	bool success = false;
	sf::Image image;
	sf::Vector2u size;
	std::vector<sf::Image> extractedImages;


	if (image.loadFromFile(filepath))
	{
		size = image.getSize();

		if (readRegionPosStart.x > size.x ||
			readRegionPosStart.y > size.y ||
			readRegionPosEnd.x > size.x ||
			readRegionPosEnd.y > size.y)
			throw std::out_of_range
			("Read region extends outside of image size!");



		for (unsigned int i = 0;
			i < readRegionPosEnd.y - readRegionPosStart.y %
			internalSectionDimensions.y + internalVerticalOffset;
			i++)
			for (unsigned int j = 0;
				j < readRegionPosEnd.x - readRegionPosStart.x %
				internalSectionDimensions.x + internalHorizontalOffset;
				j++)
				saveImageSection
					(image, j, i, "level_" + std::to_string(i * j));
	}

	return success;
}

bool ImageExtractor::areValuesSet()
{
	return false;
}

void ImageExtractor::saveImageSection(const sf::Image& sourceImage,
	unsigned int startX, unsigned int startY, const std::string& filename)
{
	sf::Image extract;
}
