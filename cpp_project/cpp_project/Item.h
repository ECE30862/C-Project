#pragma once
#include "BaseElement.h"

class Item : public BaseElement{
private:
public:
	Action* action;
	std::string turnon;
	bool hasTurnOn;
	std::string writing;
	Item(rapidxml::xml_node<>* a_node);
	~Item();
	void printItem() const;
};