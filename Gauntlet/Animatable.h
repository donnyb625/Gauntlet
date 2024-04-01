#pragma once

#include "SharedTypes.h"

class Animatable
{
protected:
	Animatable() = default;
	virtual ~Animatable() = default;

	virtual void getTextures() = 0;

	UsableResource const * const * const animationState = nullptr;
	ResourceType animationType = ResourceType::NULL_TYPE;
	int animationFrame = 0;
};