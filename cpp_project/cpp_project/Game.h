#pragma once
#include "Map.h"

class Game {
private:
	Map * map;
	Room* cur_room;
	std::vector<Item*> inventory;
public:
	bool gameOver;
	Game(std::string filename);
	~Game();
	void printCurRoom() const;
	void command(std::string user_input);
	bool checkTriggers(std::vector<Trigger>& a_triggers, std::string str_cmd);
	bool checkAllTriggers(std::string user_input);
	void performAction(Action a_action);
	void addToRoom(Room* a_room, std::string str_add);
	void deleteFromRoom(Room* a_room, std::string str_del);
	bool checkCondition(Condition cur_cond);
};