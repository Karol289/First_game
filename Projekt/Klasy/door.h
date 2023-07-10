#pragma once

/** @brief Klasa reprezentujaca drzwi na mapie */
#include "object.h"

class door : public object
{
	int objectTouched(std::vector<std::vector<gameTile*>>& _tiles, int _posx, int _posy, int _x, int _y, std::vector<std::unique_ptr<object>>& _objects, bool _key);
	/**< Metoda wywolwywana przy dotknieciu obiektu
	* @param _tiles Pola mapy
	* @param _posy Pozycja y gracza
	* @param _posx Pozycja x gracza
	* @param _x Zmiana x gracza
	* @param _y Zmiana y gracza
	* @param objects Wektor obiektow mapy
	* @param  _key Czy postac ma klucz */

public:
	door(bool _isPassable, sf::Vector2i _objectPos, std::string _textureFile);
	/**< Konstruktor wieloargumentowy, parametry przypisuja do zmiennych wedlug nazwy */
	~door();/**< Destruktor  */
};