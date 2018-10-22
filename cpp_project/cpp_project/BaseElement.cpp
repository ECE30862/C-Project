#include "BaseElement.h"

void BaseElement::setName(const std::string& a_name) { name = a_name; }
void BaseElement::setStatus(const std::string& a_status) { status = a_status; }
void BaseElement::setDescription(const std::string& a_description) { description = a_description; }

std::string BaseElement::getName() const { return name; }
std::string BaseElement::getStatus() const { return status; }
std::string BaseElement::getDescription() const { return description; }

BaseElement::BaseElement(rapidxml::xml_node<>* a_node){
	using namespace rapidxml;
	name = a_node->first_node("name")->value();
	status = a_node->first_node("status") ? a_node->first_node("status")->value() : "";
	description = a_node->first_node("description") ? a_node->first_node("description")->value() : "";
	xml_node<>* trigger_node = a_node->first_node("trigger");
	while (trigger_node) {
		Trigger a_trigger(trigger_node);
		triggers.push_back(a_trigger);
		trigger_node = trigger_node->next_sibling("trigger");
	}
}