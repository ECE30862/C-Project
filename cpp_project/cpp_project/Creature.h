#pragma once
#include "BaseElement.h"

class Attack {
public:
	std::vector<Action> actions;
	std::vector<Condition> conditions;
	std::vector<std::string> prints;
	Attack(rapidxml::xml_node<>* a_node);
};


class Creature : public BaseElement{
public:
	std::vector<std::string> vulnerabilities;
	Attack* attk;
	Creature(rapidxml::xml_node<>* a_node);
	~Creature();
};