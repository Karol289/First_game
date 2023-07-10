
#include "exit.h"

Exit::Exit(bool _isPassable, sf::Vector2i _objectPos, std::string _textureFile)
{
	isPassable = _isPassable;
	oPos = _objectPos;

	oTexture.loadFromFile(_textureFile);
	oSprite.setTexture(oTexture);

	oSprite.setPosition(_objectPos.x * 50, _objectPos.y * 50);
	oSprite.setScale(0.5, 0.5);
}

Exit::~Exit()
{

}

int Exit::objectTouched(std::vector<std::vector<gameTile*>>& _tiles, int _posx, int _posy, int _x, int _y, std::vector<std::unique_ptr<object>>& _objects, bool _key)
{
	return 0;
}