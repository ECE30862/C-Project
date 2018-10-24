#pragma once
#include "BaseElement.h"

class Creature : public BaseElement{
private:
	std::vector<Creature*> vulnerabilities;
public:
	Creature(rapidxml::xml_node<>* a_node);
	~Creature();
};