#pragma once
#include <string>
class Creature {
private:
	std::string name;
public:
	Creature(std::string a_name);
	std::string getName() const;
};