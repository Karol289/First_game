#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#ifndef PLAYER_H
#define PLAYER_H
/** @brief Klasa reprezentujaca gracza */
class player
{
	
	sf::Vector2i playerPos;/**< Pozycja gracza*/
	sf::Sprite	pSpirit;/**< Spirit Gracza*/
	sf::Texture pTexture;/**< Tekstura gracza*/

	

public:

	player();/**< Konstruktor bezargumentowy*/

	sf::Vector2i getPlayerPos();/**< Zwraca pozycje gracza */
	sf::Sprite getSprite();/**< Zwraa Sprite gracza*/

	void setPlayerPos(sf::Vector2i xy);/**< Ustawia pozycje gracza*/
	

	//Controls
	void move_up();/**< Ruch gracza do gory */
	void move_down();/**< Ruch gracza do dolu*/
	void move_left();/**< Ruch gracza w lewo*/
	void move_right();/**< Ruch gracza w prawo*/
};

#endif // !PLAYER_H

