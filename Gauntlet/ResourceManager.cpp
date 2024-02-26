#include "ResourceManager.h"


ResourceManager::ResourceManager()
{

}


ResourceManager::~ResourceManager()
{

}


void ResourceManager::loadResources()
{

}


UsableResource ResourceManager::getSound(ResourceIdentifier consumerID,
	ResourceType type)
{
	// Search through the loaded endries from the file for the specific id and type matchup

	UsableResource::Resource * resource = new UsableResource::Resource(sf::SoundBuffer());

	return UsableResource(resource, 1, ResourceType::AMBIENT);
}


UsableResource ResourceManager::getTexture(ResourceIdentifier consumerID,
	ResourceType type)
{
	// Search through the loaded endries from the file for the specific id and type matchup

	UsableResource::Resource* resource = new UsableResource::Resource(sf::Texture());

	return UsableResource(resource, 1, ResourceType::AMBIENT);
}