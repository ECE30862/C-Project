#pragma once
#include "BaseElement.h"

class Item : public BaseElement{
private:
	Action* action;
	std::string turnon;
public:
	std::string writing;
	Item(rapidxml::xml_node<>* a_node);
	~Item();
	void printItem() const;
};