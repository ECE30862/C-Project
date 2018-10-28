#pragma once
#include <vector>

#include "BaseElement.h"
#include "Item.h"
#include "Container.h"
#include "Creature.h"

class Room : public BaseElement{
private:

	std::vector<Item*> items;
	std::vector<Container*> containers;
	Room** borders;
	std::vector<Creature*> creatures;
public:

	Room(rapidxml::xml_node<>* a_node);

	std::string type;
	std::vector<Item*>& getRefItems();
	std::vector<Container*>& getRefContainers();
	Room**& getRefBorders();
	std::vector<Creature*>& getRefCreatures();

	std::vector<Item*> getItems() const;
	std::vector<Container*> getContainers() const;
	Room** getBorders() const;
	Room* getBorder(std::string str_border) const;
	std::vector<Creature*> getCreatures() const;
};