#pragma once
#include <string>
class Item {
private:
	std::string name;
public:
	Item(std::string a_name);
	std::string getName() const;
};