#pragma once
#include <vector>

#include "BaseElement.h"
#include "Item.h"
#include "Container.h"
#include "Creature.h"

class Room : public BaseElement{
private:
	std::string type;

	std::vector<Item*> items;
	std::vector<Container*> containers;
	std::vector<Room*> borders;
	std::vector<Creature*> creatures;
public:
	Room(rapidxml::xml_node<>* a_node);
};