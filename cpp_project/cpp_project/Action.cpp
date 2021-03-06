#include "Action.h"

Action::Action(std::string action_line) {
	std::string orig_line = action_line;
	std::string str_action = action_line.substr(0, action_line.find(" "));
	action_line = action_line.erase(0, action_line.find(" ") + 1);
	if (str_action == "Update") {
		action_type = UPDATE;
		str_left = action_line.substr(0, action_line.find(" "));
		str_right = action_line.substr(action_line.find("to ") + 3);
	}
	else if (str_action == "Add") {
		action_type = ADD;
		str_left = action_line.substr(0, action_line.find(" "));
		str_right = action_line.substr(action_line.find("to ") + 3);
	}
	else if (str_action == "Delete") {
		action_type = DELETE;
		str_left = action_line;
		str_right = "";
	}
	else if (orig_line == "Game Over") {
		action_type = GAME_OVER;
		str_left = "";
		str_right = "";
	}
	else {
		action_type = CMD;
		str_left = orig_line;
		str_right = "";
	}
}

ACTION_TYPE Action::getType() const {
	return action_type;
}

std::string Action::getLeft() const {
	return str_left;
}

std::string Action::getRight() const {
	return str_right;
}