#include "Room.h"

Room::Room(std::string a_name)
	:name(a_name){
	
}

std::string Room::getName() const {
	return name;
}