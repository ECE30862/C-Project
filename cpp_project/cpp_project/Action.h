#pragma once
#include <string>

enum ACTION_TYPE {UPDATE, ADD, DELETE, NONE, GAME_OVER};

class Action {
private:
	ACTION_TYPE action_type;
	std::string str_left;
	std::string str_right;
public:
	Action(std::string action_line);
	ACTION_TYPE getType() const;
	std::string getLeft() const;
	std::string getRight() const;
};