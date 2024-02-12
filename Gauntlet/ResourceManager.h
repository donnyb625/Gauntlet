#pragma once

#include "SharedTypes.h"


class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();


private:
	struct ManagedResource
	{
		const UsableResource resource;
		const ResourceIdentifier identifier;

		ManagedResource(int count, 
			UsableResource initResource, ResourceIdentifier initID)
			: resource(initResource), identifier(initID) {}
	};

	ManagedResource* textures;
	ManagedResource* sounds;
};

