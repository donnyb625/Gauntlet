#pragma once

#include "SharedTypes.h"


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

	ManagedResource** managedTextures = nullptr;
	ManagedResource** managedSounds = nullptr;

	sf::Texture** textures = nullptr;
	sf::SoundBuffer** sounds = nullptr;

	int totalTextures = 0, totalSounds = 0;

	void loadResources();
};

