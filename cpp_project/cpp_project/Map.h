#pragma once
#include "rapidxml-1.13/rapidxml.hpp"
#include "Room.h"
#include "Item.h"
#include "Container.h"
#include "Creature.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>


class Map {
private:
	std::vector<Room*> rooms;
	std::vector<Item*> items;
	std::vector<Container*> containers;
	std::vector<Creature*> creatures;
public:
	Map(std::string filename);
	~Map();
};