#include "Container.h"

Container::Container(rapidxml::xml_node<>* a_node)
	: BaseElement(a_node){
}

std::vector<Item*>& Container::getRefItems() { return items; }

std::vector<Item*> Container::getItems() { return items; }