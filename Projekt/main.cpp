#include <SFML/Graphics.hpp>

#include "Klasy/moves.h"

#include <iostream>


int main()
{
	
	double window_height = 700;
	double window_width = 700;		
	sf::RenderWindow window(sf::VideoMode(window_height, window_width), "Gierka");

	
	gameWorld world;
	moves Moves(world.getGridY());

	world.showControlls();

	while (window.isOpen())
	{
		sf::Event event;
		
		while (window.pollEvent(event))
		{
			world.chechEvents(window, event);
		}

		
		world.checkIfOnExit(Moves.getText());
		
		Moves.setString(std::to_string(world.getMoves()));


		window.clear();

		
		world.drawTiles(window);

		world.drawPlayer(window);

		world.drawObjects(window);

		Moves.drawMoves(window);

		

		window.display();


		world.checkRemainingMoves();
		
	}
}