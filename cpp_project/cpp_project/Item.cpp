#include "Item.h"

Item::Item(rapidxml::xml_node<>* a_node)
	: BaseElement(a_node){
	using namespace rapidxml;

	writing = a_node->first_node("writing") ? a_node->first_node("writing")->value() : "";
	if (a_node->first_node("turnon")) {
		turnon = a_node->first_node("turnon")->first_node("print") ? a_node->first_node("turnon")->first_node("print")->value() : "";
		action = new Action(a_node->first_node("turnon")->first_node("action")->value());
	}
	else {
		turnon = "";
		action = NULL;
	}
}

Item::~Item() {
	delete action;
}

void Item::printItem() const {
	using namespace std;
	cout << "Item name: " << name << "\n";
	cout << "Description: " << description << "\n";
	cout << "Status: " << status << "\n";
	cout << "Writing: " << writing << "\n";
	if (action != NULL) {
		cout << "Turnon: action - " << action->getType() << " " << action->getLeft() << " " << action->getRight() << " " << turnon << "\n";
	}
}
