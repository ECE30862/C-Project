#pragma once
#include "Map.h"

class Game {
private:
	Map * map;
	Room* cur_room;
	std::vector<Item*> inventory;
public:
	Game(std::string filename);
	~Game();
	void printCurRoom() const;
	void command(std::string user_input);
	bool checkTriggers(std::vector<Trigger>& a_triggers, std::string str_cmd);
	bool checkAllTriggers(std::string user_input);
	void performAction(Action a_action);
};