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
						else if(cur_cond.owner == cur_room->getName()){
							for (int k = 0; k < cur_room->getItems().size(); k++) {
								if (cur_cond.has && cur_room->getItems()[k]->getName() == cur_cond.object) {
									triggered = true;
									break;
								}
								else if (!cur_cond.has && cur_room->getItems()[k]->getName() == cur_cond.object) {
									triggered = false;
									break;
								}
							}
						
						}
						else {
							for (int k = 0; k < cur_room->getContainers().size(); k++) {
								if (cur_cond.owner == cur_room->getContainers()[k]->getName()) {
									for (int p = 0; p < cur_room->getContainers()[k]->getItems().size(); p++) {
										if (cur_cond.has && cur_room->getContainers()[k]->getItems()[p]->getName() == cur_cond.object) {
											triggered = true;
											break;
										}
										else if (!cur_cond.has && cur_room->getContainers()[k]->getItems()[p]->getName() == cur_cond.object) {
											triggered = false;
											break;
										}
									}
								}
								if (triggered) {
									break;
								}
							}
						}
					}
					else {
						//status check
						if (cur_cond.object == cur_room->getName() && cur_cond.status == cur_room->getStatus()) {
							triggered = true;
						}
						else {
							//items in room
							for (int k = 0; k < cur_room->getItems().size(); k++) {
								if (cur_cond.object == cur_room->getItems()[k]->getName() && cur_cond.status == cur_room->getItems()[k]->getStatus()) {
									triggered = true;
									break;
								}
							}
							if (triggered) {
								break;
							}
							//containers in room
							for (int k = 0; k < cur_room->getContainers().size(); k++) {
								if (cur_cond.object == cur_room->getContainers()[k]->getName() && cur_cond.status == cur_room->getContainers()[k]->getStatus()) {
									triggered = true;
									break;
								}
								for (int p = 0; p < cur_room->getContainers()[k]->getItems().size(); p++) {
									if (cur_cond.object == cur_room->getContainers()[k]->getItems()[p]->getName() && cur_cond.status == cur_room->getContainers()[k]->getItems()[p]->getStatus()) {
										triggered = true;
										break;
									}
								}
								if (triggered) {
									break;
								}
							}
							
						}
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
					for (int j = 0; j < cur_trig.actions.size(); j++) {
						performAction(cur_trig.actions[j]);
					}

					cur_trig.used = true;
					for (int j = 0; j < cur_trig.prints.size(); j++) {
						std::cout << cur_trig.prints[j] << "\n";
					}
				}
			}
			else {
				//perform actions
				for (int j = 0; j < cur_trig.actions.size(); j++) {
					performAction(cur_trig.actions[j]);
				}

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
	}
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
			if (!itemFound) {
				for (int i = 0; i < cur_room->getContainers().size(); i++) {

					if (cur_room->getContainers()[i]->open) {
						for (int j = 0; j < cur_room->getContainers()[i]->getItems().size(); j++) {
							if (cur_room->getContainers()[i]->getItems()[j]->getName() == input) {
								Item* changing_item = cur_room->getContainers()[i]->getItems()[j];
								cur_room->getContainers()[i]->getRefItems().erase(cur_room->getContainers()[i]->getRefItems().begin() + i);
								inventory.push_back(changing_item);
								itemFound = true;
								cout << "Item " << changing_item->getName() << " added to inventory.\n";
								break;
							}
						}
					}
					if (itemFound) {
						break;
					}
				}
			}
			
			if (!itemFound) {
				cout << "Error\n";
			}
		}
	}
	else if (str_cmd == "open") {
		if (!checkAllTriggers(user_input)) {
			bool containerFound = false;
			for (int i = 0; i < cur_room->getContainers().size(); i++) {
				if (cur_room->getContainers()[i]->getName() == input) {
					cout << cur_room->getContainers()[i]->getName() << " ";
					if (cur_room->getContainers()[i]->getItems().size() == 0) {
						cout << "is empty.\n";
					}
					else {
						cout << "contains ";
						for (int j = 0; j < cur_room->getContainers()[i]->getItems().size(); j++) {
							cout << cur_room->getContainers()[i]->getItems()[j]->getName();
							if (j < cur_room->getContainers()[i]->getItems().size() - 1) {
								cout << ", ";
							}
							else {
								cout << ".\n";
							}
						}
					}
					containerFound = true;
					break;
				}
			}
			if (!containerFound) {
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