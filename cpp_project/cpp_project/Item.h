#pragma once
#include "BaseElement.h"
#include "Action.h"
class Item : public BaseElement{
private:
	std::string writing;
	Action* action;
	std::string turnon;
public:
	Item(rapidxml::xml_node<>* a_node);
	~Item();
	void printItem() const;
};