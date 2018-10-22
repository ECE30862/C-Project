#include "Game.h"

Game::Game(std::string filename) {
	map = new Map(filename);
	cur_room = map->getEntrance();
}

Game::~Game() {
	delete map;
}



void Game::printCurRoom() const {
	std::cout << cur_room->getDescription() << "\n";
}

bool Game::checkTriggers(std::vector<Trigger>& a_triggers, std::string str_cmd) {
	bool cmd_block = false;
	for (int i = 0; i < a_triggers.size(); i++) {
		bool triggered = false;
		Trigger& cur_trig = a_triggers[i];
		if (cur_trig.useType || (!cur_trig.useType && !cur_trig.used)) {
			if (cur_trig.conditions.size() > 0) {
				for (int j = 0; j < cur_trig.conditions.size(); j++) {
					Condition cur_cond = cur_trig.conditions[j];
					if (cur_cond.hasType) {
						triggered = !cur_cond.has;
						if (cur_cond.owner == "inventory") {
							for (int k = 0; k < inventory.size(); k++) {
								if (cur_cond.has && inventory[k]->getName() == cur_cond.object) {
									triggered = true;
									break;
								}
								else if (!cur_cond.has && inventory[k]->getName() == cur_cond.object) {
									triggered = false;
									break;
								}
							}
						}
						else {
							/*
							for (int k = 0; k < map->rooms.size(); k++) {
								if (cur_cond.owner == map->rooms[k]->getName()) {
									for (int p = 0; p < map->rooms[k]->getItems().size(); p++) {
										if (cur_cond.has && inventory[k]->getName() == cur_cond.object) {
											triggered = true;
											break;
										}
										else if (!cur_cond.has && inventory[k]->getName() == cur_cond.object) {
											triggered = false;
											break;
										}
									}
								}
								for (int p = 0; p < map->rooms[k]->getContainers().size(); p++) {
									if (cur_cond.owner == map->rooms[k]->getContainers()[p]->getName()) {
										
										break;
									}
								}
								
							}*/
						}
					}
					else {
						//status check

					}
					if (!triggered) {
						break;
					}
				}
			}
			else {
				triggered = true;
			}
		}

		if (triggered) {
			if (cur_trig.commands.size() != 0) {
				for (int j = 0; j < cur_trig.commands.size(); j++) {
					if (cur_trig.commands[j] == str_cmd) {
						cmd_block = true;
						break;
					}
				}
				if (cmd_block) {
					//perform actions

					cur_trig.used = true;
					for (int j = 0; j < cur_trig.prints.size(); j++) {
						std::cout << cur_trig.prints[j] << "\n";
					}
				}
			}
			else {
				//perform actions

				cur_trig.used = true;
				for (int j = 0; j < cur_trig.prints.size(); j++) {
					std::cout << cur_trig.prints[j] << "\n";
				}
			}
			
		}
	}
	return cmd_block;
}

bool Game::checkAllTriggers(std::string user_input) {
	bool cmd_block = false;
	cmd_block = cmd_block || checkTriggers(cur_room->triggers, user_input);
	/*
	for (int i = 0; i < cur_room->getCreatures().size(); i++) {
	cmd_block = cmd_block || checkTriggers(cur_room->getCreatures()[i]->triggers, user_input);
	}
	for (int i = 0; i < cur_room->getContainers().size(); i++) {
	cmd_block = cmd_block || checkTriggers(cur_room->getContainers()[i]->triggers, user_input);
	for (int j = 0; j < cur_room->getContainers()[i]->getItems().size(); j++) {
	cmd_block = cmd_block || checkTriggers(cur_room->getContainers()[i]->getItems()[j]->triggers, user_input);
	}
	}
	for (int i = 0; i < cur_room->getItems().size(); i++) {
	cmd_block = cmd_block || checkTriggers(cur_room->getItems()[i]->triggers, user_input);
	}*/
	return cmd_block;
}

void Game::performAction(Action a_action) {

}

//this function is for user inputs
void Game::command(std::string user_input) {
	using namespace std;
	std::string input = user_input;
	string str_cmd = user_input.substr(0, user_input.find(" "));
	input.erase(0, input.find(" ") + 1);
	
	if (str_cmd == "n" || str_cmd == "s" || str_cmd == "w" || str_cmd == "e") {
		if (!checkAllTriggers(user_input)) {
			if (cur_room->getBorder(str_cmd)) {
				cur_room = cur_room->getBorder(str_cmd);
				printCurRoom();
			}
			else {
				cout << "You can't go that way.\n";
			}
		}
	}
	else if (str_cmd == "i") {
		if (!checkAllTriggers(user_input)) {
			cout << "Inventory: ";
			if (inventory.size() == 0) {
				cout << "empty\n";
			}
			else {
				for (int i = 0; i < inventory.size(); i++) {
					cout << inventory[i]->getName();
					if (i != (inventory.size() - 1)) {
						cout << ", ";
					}
					else {
						cout << "\n";
					}
				}
			}
		}
	}
	else if (str_cmd == "take") {
		if (!checkAllTriggers(user_input)) {
			bool itemFound = false;
			std::vector<Item*> temp_items = cur_room->getItems();
			for (int i = 0; i < cur_room->getItems().size(); i++) {
				if (cur_room->getItems()[i]->getName() == input) {
					Item* changing_item = cur_room->getItems()[i];
					cur_room->getRefItems().erase(cur_room->getRefItems().begin() + i);
					inventory.push_back(changing_item);
					itemFound = true;
					cout << "Item " << changing_item->getName() << " added to inventory.\n";
					break;
				}
			}
			//check containers
			/*
			THIS NEEDS TO BE DONE
			CREATE ACCEPT ARRAY
			"PUT KEY IN LOCK"
			CREATE IN H FILE AS WELL
			*/
			
			if (!itemFound) {
				cout << "Error\n";
			}
		}
	}
	else if (str_cmd == "print") {
		map->printLists();
	}
	else{
		cout << "Error\n";
	}
	/*
	FINISH REST OF COMMANDS
	*/
}