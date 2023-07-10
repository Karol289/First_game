/**
* @file gameWorld.h
*/


#pragma once
#include "gameTile.h"
#include "player.h"
#include "object.h"
#include "skeleton.h"
#include "brick.h"
#include "spikes.h"
#include "key.h"
#include "door.h"
#include "exit.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#ifndef GAMEWORLD_H
#define GAMEWORLD_H


/** @brief Klasa reprezentujaca mape */
class gameWorld
{
	int levelNumber; /**< Numer aktualnego poziomu */
	int gridLenght_x; /**< Szerokosc mapy*/
	int gridLenght_y; /**< Wysokosc mapy */

	int moves; /**< Ilosc pozostalych ruchow*/
	bool keyCollected;/**< Czy klucz zostal zebrany*/

	bool spikesOut; /**< Czy mapa posiada chowajace/wyskakujace kolce*/
	int spikesState; /**< Aktualny stan kolcow na mapie*/

	std::vector<std::vector<gameTile*>> tiles; /**< Macierz pol */
	std::vector<std::unique_ptr<object>> objects; /**< Wektor obiektow na mapie*/
	std::vector<std::unique_ptr<object>> objectSpikes;/**< Wektor kolcow na mapie*/

	std::unique_ptr<player> _player;/**< Gracz */
	sf::Vector2i exitPos; /**< Pozycja na ktorej ma wygenerowac sie obiekt Exit */

	void addTilesRow(std::vector<std::string>& _string, int& _row); 
	/**< Metoda dodajaca wiersz pol*
	* @param _string String ktory mowi jakie pola ma wygenerowac metoda 
	* @param _row Przekazywany int mowiacy ktory aktualnie wiersz mamy
	*/
	void addObject(std::string& _type, std::string& _x, std::string& _y); 
	/**< Metoda dodajaca obiekt
	* @param _type Okresli jakie obiekt ma byc dodany
	* @param _x okresla polozenie x 
	* @param _y okresla polozenie y */
	void restartMap(); /**< Metoda restartujaca mape*/

public:

	gameWorld(int selectedLv = 1);/**< Konstruktor ktory generuje mape ktora podamy w selectedLv */

	int getGridY(); /**< Zwraca wysokosc mapy*/
	int getMoves(); /**< Zwraca pozostale ruchy*/
	int getSpikeState(); /**< Zwraca status kolcow */

	bool cheachIfPassable(int _x, int _y); /**< Metoda sprawdzajaca czy pole na ktore chcemy da sie wejsc
	* @param _x mowi czy docelowe miejsce jest na lewo czy prawo
	* @param _y mowi czy docelowe miejsce jset u gory czy na dole */
	int checkIfObject(int x, int y);/**< Metoda ktora sprawdza czy na polu na ktory chcemy wejsc nie ma obiektu i jesli jest zwraca jego indeks
	* @param x pozycja x szukanego obiektu 
	* @param y pozycja y szukanego obiektu */
	void checkIfOnSpike(); /**< Metoda sprawdzajaca czy na koniec ruchu nie stoimy na kolcach */
	void chechEvents(sf::RenderWindow& _window, sf::Event& _event); /**< Metoda sprawdzajaca wciskane klawisze*/
	void checkIfOnExit(sf::Text _text); /**< Sprawdza czy nie weszlismy na wyjscie*/
	void checkRemainingMoves(); /**< Sprawdza pozostale ruchy, jesli ich nie mamy restartuje poziom*/

	void drawPlayer(sf::RenderWindow& _window); /**< Rysuje gracza w oknie*/
	void drawObjects(sf::RenderWindow& _window);/**< Rysuje obiekty w oknie*/
	void drawTiles(sf::RenderWindow& _window); /**< Rysuje pola w oknie*/
	
	void showControlls();

	void operator--(int); /**< Operator zmniejszajacy moves o 1*/
	bool operator++(int); /**< Operator zwracajacy true jesli gracz stoi na wyjsciu */
};

#endif // !GAMEWORLD_H



