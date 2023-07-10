#pragma once
#include "gameWorld.h"
/**  Klasa uzywana do wyswietlania pozostalych ruchow */
class moves
{
	sf::Font font;/**< Czcionka tekstu*/
	sf::Text text;/**< Tekst do ktorego przypisujemy string, font... */

public:

	moves(int _gridY);/**< Konstruktor jedno argumentowy
	* @param _gridY wysokosc mapy potrzebna do odpowiedniego ustawienia tekstu */
	void setString(std::string); /** Ustawia string do tekstu	*/
	void drawMoves(sf::RenderWindow& _window); /** Metoda rysujaca tekst w oknie*/
	sf::Text getText(); /** Zwraca zmienna Tekst*/
};
