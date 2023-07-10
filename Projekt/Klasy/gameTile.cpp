
#include "gameTile.h"


gameTile::gameTile(std::string textureName, double x, double y, bool passable)
{

	if (!setUpSprite(textureName))
	{
		return;
	}
	pos = sf::Vector2f(x, y);
	sprite.setPosition(pos);
	isPassable = passable;
};

bool gameTile::setUpSprite(std::string textureName)
{
	if (!texture.loadFromFile(textureName))
	{
		return false;
	}

	texture.setSmooth(true);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
	return true;
}; 