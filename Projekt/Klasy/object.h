#pragma once


#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include "gameTile.h"

/** @brief Klasa reprezentujaca obiekt na mapie */
class object
{
protected:

	bool isPassable; /**< Czy da sie wejsc na obiekt */
	sf::Vector2i oPos; /**< Pozycja obiektu */
	sf::Texture oTexture; /**< Tekstura obiektu */
	sf::Sprite oSprite; /**< Sprite obiektu */



public:
	object(); /**< Konstruktor bezargumentowy */
	object(bool _isPassable, sf::Vector2i _objectPos, std::string _textureFile); 
	/**< Konstruktor wieloargumentowy, nazwy parametrow odpowiadaja ustawianym zmiennym  */
	~object(); /**< Destruktor */

	sf::Sprite getSprite(); /**< Zwraca zmienna Sprite */
	bool getIsPassable(); /**< Zwraca zmienna isPassable */
	sf::Vector2i getoPos(); /**< Zwraca Pozycje */

	void movePos(int& _x, int& _y); /**< Zmienia pozycje o dane wartosci 
	* @param _x Przesuniecie w osi x
	* @param _y Przesuniecie w osi y */

	void drawObject(sf::RenderWindow& _window); /**< Rysuje obiekt w oknie */

	virtual int objectTouched(std::vector<std::vector<gameTile*>> &_tiles, int _posx, int _posy, int _x, int _y, std::vector<std::unique_ptr<object>>& _objects, bool _key)=0;
	/**< Wirtualna metoda uzywana przy dotknieciu obiektu 
	* @param _tiles Pola mapy
	* @param _posy Pozycja y gracza 
	* @param _posx Pozycja x gracza
	* @param _x Zmiana x gracza
	* @param _y Zmiana y gracza
	* @param objects Wektor obiektow mapy
	* @param  _key Czy postac ma klucz */



};
#endif // !OBJECT_H
