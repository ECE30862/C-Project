#pragma once
#include <string>

#include "rapidxml-1.13/rapidxml.hpp"

class BaseElement {
protected:
	std::string name;
	std::string status;
	std::string description;
public:

	BaseElement(rapidxml::xml_node<>* a_node);

	void setName(const std::string& a_name);
	void setStatus(const std::string& a_status);
	void setDescription(const std::string& a_description);

	std::string getName() const;
	std::string getStatus() const;
	std::string getDescription() const;
};