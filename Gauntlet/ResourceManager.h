#pragma once

#include "SharedTypes.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	UsableResource getSound(
		ResourceIdentifier consumerID, ResourceType type);
	UsableResource getTexture(
		ResourceIdentifier consumerID, ResourceType type);

private:
	struct ManagedResource
	{
		const UsableResource resource;
		const ResourceIdentifier identifier;

		ManagedResource(int count, 
			UsableResource initResource, ResourceIdentifier initID)
			: resource(initResource), identifier(initID) {}
	};

	ManagedResource** textures = nullptr;
	ManagedResource** sounds = nullptr;

	int totalTextures = 0, totalSounds = 0;

	void loadResources();
};

