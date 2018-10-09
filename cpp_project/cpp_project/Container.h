#pragma once
#include <vector>

#include "BaseElement.h"
#include "Item.h"

class Container : public BaseElement {
private:
	std::vector<Item*> items;
public:
	Container(rapidxml::xml_node<>* a_node);

	std::vector<Item*>& getRefItems();

	std::vector<Item*> getItems();
};