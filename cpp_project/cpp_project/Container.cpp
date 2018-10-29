#include "Container.h"

Container::Container(rapidxml::xml_node<>* a_node)
	: BaseElement(a_node){
	using namespace rapidxml;
	using namespace std;
	opened = false;
	xml_node<>* accept_node = a_node->first_node("accept");
	while (accept_node) {
		accept.push_back(accept_node->value());
		accept_node = accept_node->next_sibling("accept");
	}
}

std::vector<Item*>& Container::getRefItems() { return items; }

std::vector<Item*> Container::getItems() { return items; }