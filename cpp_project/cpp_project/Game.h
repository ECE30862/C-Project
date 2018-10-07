#pragma once
#include "Map.h"

class Game {
private:
	Map* map;
	std::vector<Item*> inventory;
public:
	Game(std::string filename);
	~Game();
};