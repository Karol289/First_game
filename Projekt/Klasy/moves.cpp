#include "moves.h"

moves::moves(int _gridY)
{
	if (!font.loadFromFile("Grafiki/font.ttf"))
		std::cout << "font file error" << std::endl;
	text.setFont(font);
	text.setPosition(0, 50 * (_gridY - 1));
}

void moves::setString(std::string _moves)
{
	text.setString(_moves);
}

void moves::drawMoves(sf::RenderWindow& _window)
{
	_window.draw(text);
}

sf::Text moves::getText()
{
	return text;
}