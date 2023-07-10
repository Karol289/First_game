#include "object.h"

object::object()
{
	
}

object::object(bool _isPassable, sf::Vector2i _objectPos, std::string _textureFile)
{
	isPassable = _isPassable;
	oPos = _objectPos;

	oTexture.loadFromFile(_textureFile);
	oSprite.setTexture(oTexture);

	oSprite.setPosition(_objectPos.x * 50, _objectPos.y * 50);
	oSprite.setScale(0.5, 0.5);

}

object::~object() {
	
	
}

sf::Sprite object::getSprite()
{
	return oSprite;
}

bool object::getIsPassable()
{
	return this->isPassable;
}

sf::Vector2i object::getoPos()
{
	return this->oPos;
}

void object::movePos(int& _x, int& _y)
{
	oPos.x += _x;
	oPos.y += _y;
	oSprite.move(_x*50, _y*50);
}

void object::drawObject(sf::RenderWindow& _window)
{
	_window.draw(this->getSprite());
}