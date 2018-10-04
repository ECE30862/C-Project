#pragma once
#include "rapidxml-1.13/rapidxml.hpp"
#include "Room.h"

#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>


class Map {
private:
	std::vector<Room*> rooms;
public:
	Map(std::string filename);
	~Map();
};