#pragma once

#include <SFML/Graphics.hpp>
#include <utility>
#include <iostream>

#ifndef  GAMETILE_H
#define GAMETILE_H	
/** @brief Klasa reprezentujaca pole mapy*/
class gameTile
{
	sf::Vector2f pos;/**< Pozycja pola */
	sf::Texture texture;/**< Tekstura pola */


	public:
		
		bool isPassable; /**< Czy przez pole da sie przejsc */
		sf::Sprite sprite; /**< Sprite pola */


		gameTile(std::string, double, double, bool);/**< Konstruktor wielooargumentowy */
		bool setUpSprite(std::string); /**< Metoda ustawiajaca nam Sprite za pomoca nazwy pliku */
	};

#endif 
