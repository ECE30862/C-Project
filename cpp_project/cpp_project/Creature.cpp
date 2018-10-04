#include "Creature.h"

Creature::Creature(std::string a_name)
	:name(a_name) {

}

std::string Creature::getName() const {
	return name;
}