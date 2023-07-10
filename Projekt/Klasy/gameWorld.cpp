#include "gameWorld.h"
#include <fstream>

gameWorld::gameWorld(int selectedLvl)
{
	levelNumber = selectedLvl;

	std::string _lvlName = "Levele/lvl" + std::to_string(levelNumber) + ".txt";

	_player = std::unique_ptr<player>(new player());


	spikesOut = 0;
	spikesState = 1;

	std::ifstream file;
	file.open(_lvlName);

	if (file)
	{
	}
	else
	{
		file.open("Levele/end.txt");
	}
	
	std::string line;

	if (file) 
	{
		std::vector<std::string> words;

		const std::string GX{ "grid_x" };
		const std::string GY{ "grid_y" };
		const std::string PP{ "ppos" };
		const std::string EP{ "epos" };
		const std::string TR{ "trow" };
		const std::string OB{ "obj" };
		const std::string MV{ "moves" };
		const std::string SO{ "sout" };

		std::vector<std::string> border;
		int row = 0;

		while (std::getline(file, line))
		{
			const char space = ' ';
			const std::string empty = "";
			const char tab = '\t';
			const char endl = '\n'; //----------!

			std::string word;

			for (size_t i = 0; i < line.size(); i++)
			{
				if (line[i] == space or line[i] == tab)
				{
					if (word != empty)
					{
						words.push_back(word);
						word.clear();
					}
				}
				else
				{
					word.push_back(line[i]);
				}
			}
			if (word != empty)
				words.push_back(word);


			if (std::string(words[0]) == GX)
			{
				gridLenght_x = stoi(words[1]) +2;
			}
			else if (std::string(words[0]) == GY)
			{
				gridLenght_y = stoi(words[1]) +2;

				for (int i = 0; i < gridLenght_x; i++)
				{
					border.push_back("1");
				}

				addTilesRow(border, row);
			}
			else if (std::string(words[0]) == PP)
			{
				int x = stoi(words[1])+1;
				int y = stoi(words[2])+1;
				//std::cout << x << " I " << y << std::endl;
				_player->setPlayerPos(sf::Vector2i(x, y));
			}
			else if (std::string(words[0]) == EP)
			{
				exitPos = sf::Vector2i(stoi(words[1])+1, stoi(words[2])+1);
			}
			else if ((std::string(words[0]) == MV))
			{
				moves = stoi(words[1]);
			}
			else if (std::string(words[0]) == TR)
			{
				addTilesRow(words, row);
			}
			else if (std::string(words[0]) == OB)
			{
				addObject(words[1], words[2], words[3]);
			}
			else if (std::string(words[0]) == SO)
			{
				spikesOut = stoi(words[1]);
				spikesState = 0;
			}

			words.clear();
		
		}
		addTilesRow(border, row);
		
	}
	else
	{
		std::cout << "Can't open "<<_lvlName<<" file" << std::endl;
	}
	
	objects.push_back(std::unique_ptr<object>(new Exit(true, exitPos, "Grafiki/exit.png")));

}

void gameWorld::addTilesRow(std::vector<std::string>& _string, int& _row)
{
	std::vector<gameTile*> ROW;
	int column = 1;

	ROW.push_back(new gameTile("Grafiki/wall.png.", 0, _row * 50, false));

	for (auto& i : _string)
	{
		if (i == "1")
		{
			ROW.push_back(new gameTile("Grafiki/wall.png.", column*50, _row*50, false));
			column++;
		}
		else if (i == "2")
		{
			ROW.push_back(new gameTile("Grafiki/ground.png.", column * 50, _row * 50, true));
			column++;
		}

		
	}
	ROW.push_back(new gameTile("Grafiki/wall.png.", column * 50, _row * 50, false));

	tiles.push_back(ROW);

	_row++;
}

void gameWorld::addObject(std::string& _type, std::string& _x, std::string& _y)
{
	if (_type == "1") //skeleton
	{
		objects.push_back(std::unique_ptr<object>(new skeleton(false, sf::Vector2i(stoi(_x) + 1, stoi(_y) + 1), "Grafiki/enemy.png")));
	}
	else if (_type == "2") //brick
	{
		objects.push_back(std::unique_ptr<object>(new brick(false, sf::Vector2i(stoi(_x) + 1, stoi(_y) + 1), "Grafiki/brick.png")));
	}
	else if (_type == "3") //spikes
	{
		objectSpikes.push_back(std::unique_ptr<object>(new spikes(true, sf::Vector2i(stoi(_x) + 1, stoi(_y) + 1), "Grafiki/spikes.png")));
	}
	else if(_type == "4") // key
	{
		objects.push_back(std::unique_ptr<object>(new key(true, sf::Vector2i(stoi(_x) + 1, stoi(_y) + 1), "Grafiki/key.png")));
	}
	else if (_type == "5") //door
	{
		objects.push_back(std::unique_ptr<object>(new door(false, sf::Vector2i(stoi(_x) + 1, stoi(_y) + 1), "Grafiki/door.png")));
	}
}

int gameWorld::getGridY()
{
	return gridLenght_y;
}

int gameWorld::getMoves()
{
	return moves;
}

int gameWorld::getSpikeState()
{
	return spikesState;
}

bool gameWorld::cheachIfPassable(int _x, int _y)
{
	sf::Vector2i pos = _player->getPlayerPos();
	int pos_x = pos.x + _x;
	int pos_y = pos.y + _y;

	//std::cout << pos_x << " ,  " << pos_y <<", "<<tiles[pos_x][pos_y]->isPassable<< std::endl;
	bool end = false;
	int c = 0;
	if (tiles[pos_y][pos_x]->isPassable == true)
	{
		int objectID = checkIfObject(pos_x, pos_y);
		if (objectID != -1)
		{
			if (!objects[objectID]->getIsPassable())
				c = 1;

			int b = objects[objectID]->objectTouched(tiles, pos_x, pos_y, _x, _y, objects, keyCollected);
			if (b == 1)
				objects.erase(objects.begin()+objectID);
			else if (b == 2)
			{
				objects.erase(objects.begin() + objectID);
				keyCollected = true;
			}
			
		}
		end = true;
	}
	if (c == 1) {
		return false;
	}
	return end;
}

int gameWorld::checkIfObject(int x, int y)
{
	//std::cout << "Aaa" << std::endl;
	//std::cout << _player->getPlayerPos().x << " , " << _player->getPlayerPos().y << std::endl;
	//std::cout << exitPos.x << " , " << exitPos.y << std::endl;

	for (int i = 0; i < objects.size(); i++)
	{
		sf::Vector2i pos = objects[i]->getoPos();
		if (pos.x == x and pos.y == y) {
			return i;
		}
	}
	return -1;
	
}

void gameWorld::checkIfOnSpike()
{
	if ((spikesOut == 0 and spikesState == 1) or (spikesState == 0 and spikesOut == 1)) {
		for (auto& i : objectSpikes)
		{
			if (i->getoPos() == _player->getPlayerPos())
			{
				moves--;
			}
		}
	}

	if (spikesOut == true)
	{
		if (spikesState == 0)
		{
			spikesState = 2;
		}
		else if (spikesState == 1)
		{
			spikesState = 3;
		}
	}
}

void gameWorld::chechEvents(sf::RenderWindow& _window, sf::Event& _event)
{
	
		if (sf::Event::Closed == _event.type)
			{
				_window.close();
			 }
		if (_event.type == sf::Event::KeyPressed)
			{
				//WASD
				
				if (_event.key.code == sf::Keyboard::W)
				{
					(*this)--;
					if(cheachIfPassable( 0, -1))
						_player->move_up();
						checkIfOnSpike();
				}
				else if (_event.key.code == sf::Keyboard::A)
				{
					(*this)--;
					if (cheachIfPassable(-1, 0))
						_player->move_left();
						checkIfOnSpike();
				}
				else if (_event.key.code == sf::Keyboard::S)
				{
					(*this)--;
					if (cheachIfPassable(0, 1))
						_player->move_down();
						checkIfOnSpike();
				}
				else if (_event.key.code == sf::Keyboard::D)
				{
					(*this)--;
					if (cheachIfPassable(1, 0))
						_player->move_right();
						checkIfOnSpike();
				}
				//ESC
				else if (_event.key.code == sf::Keyboard::Escape)
				{
					_window.close();
				}
				//Restart
				else if (_event.key.code == sf::Keyboard::R)
				{
					restartMap();
				}
	}
}

void gameWorld::checkIfOnExit(sf::Text _text)
{
	if ((*this)++)
	{
		levelNumber++;

		*this = gameWorld(levelNumber);

		_text.setPosition(0, 50 * (getGridY() - 1));
	}
}

void gameWorld::checkRemainingMoves()
{
	if (moves <= 0)
	{
		restartMap();
	}

	if (spikesOut == true)
	{
		if (spikesState == 2)
		{
			spikesState = 1;
		}
		else if (spikesState == 3)
		{
			spikesState = 0;
		}
	}

}

void gameWorld::restartMap()
{
	*this = gameWorld(levelNumber);
}

void gameWorld::drawPlayer(sf::RenderWindow& _window)
{
	_window.draw(_player->getSprite());
}

void gameWorld::drawObjects(sf::RenderWindow& _window)
{
	if (spikesState == 1 or spikesState == 3) {
		for (auto& i : objectSpikes)
		{
			i->drawObject(_window);
		}
	}
	

	for (auto& i : objects)
	{
		i->drawObject(_window);
	}
}

void gameWorld::drawTiles(sf::RenderWindow& _window)
{
	//std::cout << gridLenght_x << " " << gridLenght_y << std::endl;
	
	for (int i = 0; i < gridLenght_y; i++)
	{
		for (int j = 0; j < gridLenght_x; j++)
		{
			_window.draw(tiles[i][j]->sprite);
		}

	}
}

void gameWorld::showControlls()
{
	std::cout << "Controls: " << std::endl;
	std::cout << "W -> move up" << std::endl;
	std::cout << "A -> move left" << std::endl;
	std::cout << "S -> move down" << std::endl;
	std::cout << "D -> move right" << std::endl;
	std::cout << "R -> restart level" << std::endl;
	std::cout << "ESC -> exit game" << std::endl;
}

void gameWorld::operator--(int) 
{
	moves=moves-1;
}

bool gameWorld::operator++(int)
{
	
	if (_player->getPlayerPos() == exitPos)
		return true;

		return false;
}

