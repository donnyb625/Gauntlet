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
	// This is where the linker errors come from; they will resolve
	// when we make this.
	ManagedResource** textures = nullptr;
	ManagedResource** sounds = nullptr;

	int totalTextures = 0, totalSounds = 0;

	void loadResources();
};

