#include "SpriteFactory.h"

ProtoEng::SpriteFactory::SpriteFactory()
	: textures(0)
{
}

ProtoEng::SpriteFactory::~SpriteFactory()
{
}

 size_t ProtoEng::SpriteFactory::loadTexture(std::string path)
{
	 textures.push_back(sf::Texture()); //Create Texture
	 
	 //Load
	 if (!textures.back().loadFromFile(path)) warnLog("Cannot Load Texture: " + path);

	 return textures.size() - 1;
}

const sf::Texture & ProtoEng::SpriteFactory::getTexture(size_t id) const
{
	if (id < textures.size())
		return textures[id];
	else
	{
		warnLog("Texture ID out of range: " + id);
		return textures[0];
	}
}

 sf::Sprite ProtoEng::SpriteFactory::getSprite(size_t id) const
{
	 sf::Sprite ret;
	 ret.setTexture(getTexture(id));

	 return ret;
}

std::string ProtoEng::SpriteFactory::custom_log_header() const
 {
	 return "::SpriteFactory::";
 }
