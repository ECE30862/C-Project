#include "Creature.h"

Attack::Attack(rapidxml::xml_node<>* a_node) {
	using namespace rapidxml;
	using namespace std;
	
	xml_node<>* condition_node = a_node->first_node("condition");
	xml_node<>* print_node = a_node->first_node("print");
	xml_node<>* action_node = a_node->first_node("action");
	while (condition_node || print_node || action_node) {
		
		if (condition_node) {
			Condition a_condition;
			a_condition.hasType = false;
			a_condition.has = false;
			a_condition.object = condition_node->first_node("object")->value();
			if (condition_node->first_node("has")) {
				a_condition.hasType = true;
				a_condition.has = condition_node->first_node("has")->value() == (string)"yes" ? true : false;
				a_condition.owner = condition_node->first_node("owner")->value();
			}
			else {
				a_condition.status = condition_node->first_node("status")->value();
			}
			conditions.push_back(a_condition);
			condition_node = condition_node->next_sibling("condition");

		}
		if (print_node) {
			prints.push_back(print_node->value());
			print_node = print_node->next_sibling("print");
		}
		if (action_node) {
			Action a_action(action_node->value());
			actions.push_back(a_action);
			action_node = action_node->next_sibling("action");
		}
	}
}

Creature::Creature(rapidxml::xml_node<>* a_node)
	:BaseElement(a_node){
	using namespace rapidxml;
	using namespace std;

	xml_node<>* vuln_node = a_node->first_node("vulnerability");
	while (vuln_node) {
		vulnerabilities.push_back(vuln_node->value());
		vuln_node = vuln_node->next_sibling("vulnerability");
	}
	xml_node<>* attk_node = a_node->first_node("attack");
	if (attk_node) {
		attk = new Attack(attk_node);
	}
}

Creature::~Creature() {
	delete attk;
}
