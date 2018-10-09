#include "Room.h"

Room::Room(rapidxml::xml_node<>* a_node)
	: BaseElement(a_node){
	using namespace rapidxml;

	type = a_node->first_node("type") ? a_node->first_node("type")->value() : "regular";
	borders = new Room*[4];
	for (int i = 0; i < 4; i++) {
		borders[i] = NULL;
	}
}


std::vector<Item*>& Room::getRefItems() { return items; }
std::vector<Container*>& Room::getRefContainers() { return containers; }
Room**& Room::getRefBorders() { return borders; }
std::vector<Creature*>& Room::getRefCreatures() { return creatures; }

std::vector<Item*> Room::getItems() const { return items; }
std::vector<Container*> Room::getContainers() const { return containers; }
Room** Room::getBorders() const { return borders; }
std::vector<Creature*> Room::getCreatures() const { return creatures; }

Room* Room::getBorder(std::string str_border) const {
	if (str_border == "n") {
		return borders[0];
	}
	else if (str_border == "s") {
		return borders[1];
	}
	else if (str_border == "w") {
		return borders[2];
	}
	else if (str_border == "e") {
		return borders[3];
	}
	return NULL;
}