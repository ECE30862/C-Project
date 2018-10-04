#include "Item.h"

Item::Item(std::string a_name)
	:name(a_name){

}

std::string Item::getName() const {
	return name;
}