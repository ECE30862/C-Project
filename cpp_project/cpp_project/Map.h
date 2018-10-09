#pragma once
#include "Room.h"

class Map {
private:
	std::vector<Room*> rooms;
	std::vector<Item*> items;
	std::vector<Container*> containers;
	std::vector<Creature*> creatures;
public:
	Map(std::string filename);
	~Map();

	void printLists() const;
	Room* getEntrance() const;
};