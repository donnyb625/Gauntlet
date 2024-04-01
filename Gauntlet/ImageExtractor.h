#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class ImageExtractor
{
public:
	ImageExtractor(std::string initPath);

	void setReadRegionStart(int x, int y);
	void setReadRegionEnd(int x, int y);
	void setInternalDimensions(int width, int height);

	void setInternalHorizOffset(int val);
	void setInternalVertOffset(int val);

	bool extractImages();
private:
	sf::Vector2i readRegionPosStart, readRegionPosEnd,
		internalSectionDimensions;
	int internalHorizontalOffset, internalVerticalOffset;
	std::string filepath;

	bool areValuesSet();

	void saveImageSection(const sf::Image& sourceImage, unsigned int startX,
		unsigned int startY, const std::string& filename);
};

