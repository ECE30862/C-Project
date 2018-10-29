#pragma once
#include <vector>

#include "BaseElement.h"
#include "Item.h"

class Container : public BaseElement {
private:
	std::vector<Item*> items;
public:
	bool opened;
	std::vector<std::string> accept;
	Container(rapidxml::xml_node<>* a_node);

	std::vector<Item*>& getRefItems();

	std::vector<Item*> getItems();
};