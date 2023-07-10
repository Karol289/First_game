
#include "skeleton.h"


skeleton::skeleton(bool _isPassable, sf::Vector2i _objectPos, std::string _textureFile)
{
	isPassable = _isPassable;
	oPos = _objectPos;

	oTexture.loadFromFile(_textureFile);
	oSprite.setTexture(oTexture);

	oSprite.setPosition(_objectPos.x * 50, _objectPos.y * 50);
	oSprite.setScale(0.5, 0.5);
}
skeleton::~skeleton() 
{
	object::~object();
}


int skeleton::objectTouched(std::vector<std::vector<gameTile*>>& _tiles,  int _posx, int _posy, int _x, int _y, std::vector<std::unique_ptr<object>>& _objects, bool _key)
{
	
	if (_tiles[_posy + _y][_posx + _x]->isPassable) {
		for (auto& i : _objects)
		{
			if (i->getoPos() == sf::Vector2i(_posx + _x, _posy + _y) and i->getIsPassable() == false)
			{
				return 1;
			}
		}
		this->movePos(_x, _y);
		return 0; //nic
	}
	else
	{
		return 1; //zniszczyc
	}
	
}