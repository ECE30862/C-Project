#include "Trigger.h"

Trigger::Trigger(rapidxml::xml_node<>* a_node) {
	using namespace rapidxml;
	using namespace std;
	if (a_node->first_node("type")) {
		useType = (a_node->first_node("type")->value() == (string) "permanent") ?
			true : false;
	}
	else {
		useType = false;
	}
	used = false;
	xml_node<>* command_node = a_node->first_node("command");
	xml_node<>* condition_node = a_node->first_node("condition");
	xml_node<>* print_node = a_node->first_node("print");
	xml_node<>* action_node = a_node->first_node("action");
	while (command_node || condition_node || print_node || action_node) {
		if (command_node) {
			commands.push_back(command_node->value());
			command_node = command_node->next_sibling("command");
		}
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