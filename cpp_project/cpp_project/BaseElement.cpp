#include "BaseElement.h"

void BaseElement::setName(const std::string& a_name) { name = a_name; }
void BaseElement::setStatus(const std::string& a_status) { status = a_status; }
void BaseElement::setDescription(const std::string& a_description) { description = a_description; }

std::string BaseElement::getName() const { return name; }
std::string BaseElement::getStatus() const { return status; }
std::string BaseElement::getDescription() const { return description; }

BaseElement::BaseElement(rapidxml::xml_node<>* a_node){
	name = a_node->first_node("name")->value();
	status = a_node->first_node("status") ? a_node->first_node("status")->value() : "";
	description = a_node->first_node("description") ? a_node->first_node("description")->value() : "";
}