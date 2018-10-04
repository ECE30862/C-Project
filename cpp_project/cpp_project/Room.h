#pragma once
#include <string>

class Room {
private:
	std::string name;
public:
	Room(std::string a_name);

	std::string getName() const;
};