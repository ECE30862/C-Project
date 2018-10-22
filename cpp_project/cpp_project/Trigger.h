#pragma once
#include <string>
#include <vector>
#include "Action.h"

#include <stdio.h>
#include <iostream>
#include <fstream>

#include "rapidxml-1.13/rapidxml.hpp"

struct Condition {
	std::string owner;
	std::string status;
	std::string object;
	bool hasType;
	bool has;
};

class Trigger {
public:
	std::vector<Action> actions;
	std::vector<Condition> conditions;
	std::vector<std::string> prints;
	std::vector<std::string> commands;
	bool useType;
	bool used;
	Trigger(rapidxml::xml_node<>* a_node);
};