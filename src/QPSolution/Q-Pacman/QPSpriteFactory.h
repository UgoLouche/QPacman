#pragma once

#include "SpriteFactory.h"

#include "SFML\Graphics.hpp"

class QPSpriteFactory : public ProtoEng::SpriteFactory
{
public:
	QPSpriteFactory();
	~QPSpriteFactory();

	sf::Sprite getTestSprite() const;
	sf::Sprite getPlayerSprite() const;
	sf::Sprite getGumSprite() const;
	sf::Sprite getSupGumSprite() const;
	sf::Sprite getGhostSprite() const;

	//Buttons are a bit different
	const sf::Texture& getButtonTexture() const;

private:
	size_t testTextureID;
	size_t playerTextureID;
	size_t buttonsTextureID;
	size_t gumTextureID;
	size_t supGumTextureID;
	size_t ghostTextureID;
};