#include "Container.h"

Container::Container(std::string a_name)
	:name(a_name) {

}

std::string Container::getName() const {
	return name;
}