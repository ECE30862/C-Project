#pragma once
#include "Room.h"

class Map {
public:
	std::vector<Room*> rooms;
	std::vector<Item*> items;
	std::vector<Container*> containers;
	std::vector<Creature*> creatures;

	Map(std::string filename);
	~Map();

	void printLists() const;
	Room* getEntrance() const;
};