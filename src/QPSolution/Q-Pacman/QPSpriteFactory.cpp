#include "QPSpriteFactory.h"

#include "const.h"

QPSpriteFactory::QPSpriteFactory()
{
	testTextureID = loadTexture(TEST_TEXTURE);
	playerTextureID = loadTexture(PLAYER_TEXTURE);
	buttonsTextureID = loadTexture(BUTTONS_TEXTURE);
	gumTextureID = loadTexture(GUM_TEXTURE);
	supGumTextureID = loadTexture(SGUM_TEXTURE);
	ghostTextureID = loadTexture(GHOST_TEXTURE);	
}

QPSpriteFactory::~QPSpriteFactory()
{
}

sf::Sprite QPSpriteFactory::getTestSprite() const
{	return getSprite(testTextureID);
}

sf::Sprite QPSpriteFactory::getPlayerSprite() const
{
	return getSprite(playerTextureID);
}

sf::Sprite QPSpriteFactory::getGumSprite() const
{
	return getSprite(gumTextureID);
}

sf::Sprite QPSpriteFactory::getSupGumSprite() const
{
	return getSprite(supGumTextureID);
}

sf::Sprite QPSpriteFactory::getGhostSprite() const
{
	return getSprite(ghostTextureID);
}

const sf::Texture & QPSpriteFactory::getButtonTexture() const
{
	return getTexture(buttonsTextureID);
}
