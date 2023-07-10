#include "player.h"

player::player()
{
	pTexture.loadFromFile("Grafiki/player.png");

	pSpirit.setTexture(pTexture);
	
	pSpirit.setScale(0.5, 0.5);
}



sf::Sprite player::getSprite()
{
	return pSpirit;
}


void player::setPlayerPos(sf::Vector2i xy)
{
	playerPos = xy;
	pSpirit.setPosition(xy.x*50, xy.y*50);
}

sf::Vector2i player::getPlayerPos()
{
	return playerPos;
}


void player::move_up()
{ 
	pSpirit.move(0, -50);
	playerPos.y -= 1;
}
void player::move_down()
{
	pSpirit.move(0, 50);
	playerPos.y += 1;
}
void player::move_left()
{
	pSpirit.move(-50, 0);
	playerPos.x -= 1;
}
void player::move_right()
{
	pSpirit.move(50, 0);
	playerPos.x += 1;
}