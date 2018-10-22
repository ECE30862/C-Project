#pragma once
#include "Trigger.h"

class BaseElement {
protected:
	std::string name;
	std::string status;
	std::string description;
public:
	std::vector<Trigger> triggers;
	BaseElement(rapidxml::xml_node<>* a_node);

	void setName(const std::string& a_name);
	void setStatus(const std::string& a_status);
	void setDescription(const std::string& a_description);

	std::string getName() const;
	std::string getStatus() const;
	std::string getDescription() const;
};