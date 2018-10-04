#pragma once
#include <string>
class Container {
private:
	std::string name;
public:
	Container(std::string a_name);
	std::string getName() const;
};