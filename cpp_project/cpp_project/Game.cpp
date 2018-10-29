#include "Game.h"

Game::Game(std::string filename) {
	map = new Map(filename);
	cur_room = map->getEntrance();
	gameOver = false;
}

Game::~Game() {
	delete map;
}



void Game::printCurRoom() const {
	std::cout << cur_room->getDescription() << "\n";
}

bool Game::checkCondition(Condition cur_cond) {
	bool triggered = false;
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
		else if (cur_cond.owner == cur_room->getName()) {
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
			for (int k = 0; k < inventory.size(); k++) {
				if (cur_cond.object == inventory[k]->getName() && cur_cond.status == inventory[k]->getStatus()) {
					triggered = true;
					break;
				}
			}
			
			if (!triggered) {
				//items in room
				for (int k = 0; k < cur_room->getItems().size(); k++) {
					if (cur_cond.object == cur_room->getItems()[k]->getName() && cur_cond.status == cur_room->getItems()[k]->getStatus()) {
						triggered = true;
						break;
					}
				}
			}
			
			if (!triggered) {
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
	}
	return triggered;
}

bool Game::checkTriggers(std::vector<Trigger>& a_triggers, std::string str_cmd) {
	bool cmd_block = false;
	for (int i = 0; i < a_triggers.size(); i++) {
		bool triggered = false;
		Trigger& cur_trig = a_triggers[i];
		if (cur_trig.useType || (!cur_trig.useType && !cur_trig.used)) {
			if (cur_trig.conditions.size() > 0) {
				for (int j = 0; j < cur_trig.conditions.size(); j++) {
					triggered = checkCondition(cur_trig.conditions[j]);
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

					cur_trig.used = true;
					for (int j = 0; j < cur_trig.prints.size(); j++) {
						std::cout << cur_trig.prints[j] << "\n";
					}
					for (int j = 0; j < cur_trig.actions.size(); j++) {
						performAction(cur_trig.actions[j]);
					}
				}
			}
			else {
				//perform actions

				cur_trig.used = true;
				for (int j = 0; j < cur_trig.prints.size(); j++) {
					std::cout << cur_trig.prints[j] << "\n";
				}

				for (int j = 0; j < cur_trig.actions.size(); j++) {
					performAction(cur_trig.actions[j]);
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
	bool found = false;
	bool foundDest = false;
	switch (a_action.getType()) {
	case UPDATE:
		for (int i = 0; i < map->rooms.size(); i++) {
			if (map->rooms[i]->getName() == a_action.getLeft()) {
				found = true;
				map->rooms[i]->setStatus(a_action.getRight());
				break;
			}
		}
		if (!found) {
			for (int i = 0; i < inventory.size(); i++) {
				if (inventory[i]->getName() == a_action.getLeft()) {
					found = true;
					inventory[i]->setStatus(a_action.getRight());
					break;
				}
			}
		}
		if (!found) {
			for (int i = 0; i < map->items.size(); i++) {
				if (map->items[i]->getName() == a_action.getLeft()) {
					found = true;
					map->items[i]->setStatus(a_action.getRight());
					break;
				}
			}
		}
		if (!found) {
			for (int i = 0; i < map->containers.size(); i++) {
				if (map->containers[i]->getName() == a_action.getLeft()) {
					found = true;
					map->containers[i]->setStatus(a_action.getRight());
					break;
				}
			}
		}
		if (!found) {
			for (int i = 0; i < map->creatures.size(); i++) {
				if (map->creatures[i]->getName() == a_action.getLeft()) {
					found = true;
					map->creatures[i]->setStatus(a_action.getRight());
					break;
				}
			}
		}
		break;
	case ADD:
		if (a_action.getRight() == "inventory") {
			foundDest = true;
			for (int i = 0; i < map->items.size(); i++) {
				if (map->items[i]->getName() == a_action.getLeft()) {
					inventory.push_back(map->items[i]);
					break;
				}
			}
		}
		if (!foundDest) {
			for (int i = 0; i < map->rooms.size(); i++) {
				if (map->rooms[i]->getName() == a_action.getRight()) {
					foundDest = true;
					addToRoom(map->rooms[i], a_action.getLeft());
					break;
				}
			}
		}
		if (!foundDest) {
			for (int i = 0; i < map->containers.size(); i++) {
				if (map->containers[i]->getName() == a_action.getRight()) {
					foundDest = true;
					for (int j = 0; j < map->items.size(); j++) {
						if (map->items[j]->getName() == a_action.getLeft()) {
							map->containers[i]->getRefItems().push_back(map->items[j]);
							break;
						}
					}
					break;
				}
			}
		}
		break;
	case DELETE:
		for (int i = 0; i < inventory.size(); i++) {
			if (inventory[i]->getName() == a_action.getLeft()) {
				inventory.erase(inventory.begin() + i);
				break;
			}
		}

		for (int i = 0; i < map->rooms.size(); i++) {
			if (map->rooms[i]->getName() == a_action.getLeft()) {
				Room* temp = map->rooms[i];
				map->rooms.erase(map->rooms.begin() + i);
				delete temp;
			}
			else {
				bool border = false;
				for (int b = 0; b < 4; b++) {
					if (map->rooms[i]->getBorders()[b]) {
						if (map->rooms[i]->getBorders()[b]->getName() == a_action.getLeft()) {
							map->rooms[i]->getRefBorders()[b] = NULL;
							border = true;
							break;
						}
					}
				}
				if (!border) {
					deleteFromRoom(map->rooms[i], a_action.getLeft());
				}
			}
		}

		break;
	case GAME_OVER:
		gameOver = true;
		break;
	case CMD:
		command(a_action.getLeft());
		break;
	}
}

void Game::deleteFromRoom(Room* a_room, std::string str_del) {
	for (int i = 0; i < a_room->getItems().size(); i++) {
		if (a_room->getItems()[i]->getName() == str_del) {
			a_room->getRefItems().erase(a_room->getRefItems().begin() + i);
			break;
		}
	}
	for (int i = 0; i < a_room->getCreatures().size(); i++) {
		if (a_room->getCreatures()[i]->getName() == str_del) {
			a_room->getRefCreatures().erase(a_room->getRefCreatures().begin() + i);
			break;
		}
	}
	
	for (int i = 0; i < a_room->getContainers().size(); i++) {
		if (a_room->getContainers()[i]->getName() == str_del) {
			a_room->getRefContainers().erase(a_room->getRefContainers().begin() + i);
			break;
		}
		for (int j = 0; j < a_room->getContainers()[i]->getItems().size(); j++) {
			if (a_room->getContainers()[i]->getItems()[j]->getName() == str_del) {
				a_room->getRefContainers()[i]->getRefItems().erase(a_room->getRefContainers()[i]->getRefItems().begin() + j);
				break;
			}
		}
	}
}


void Game::addToRoom(Room* a_room, std::string str_add) {
	bool found = false;
	if (!found) {
		for (int i = 0; i < map->items.size(); i++) {
			if (map->items[i]->getName() == str_add) {
				found = true;
				a_room->getRefItems().push_back(map->items[i]);
				break;
			}
		}
	}
	if (!found) {
		for (int i = 0; i < map->containers.size(); i++) {
			if (map->containers[i]->getName() == str_add) {
				found = true;
				a_room->getRefContainers().push_back(map->containers[i]);
				break;
			}
		}
	}
	if (!found) {
		for (int i = 0; i < map->creatures.size(); i++) {
			if (map->creatures[i]->getName() ==str_add) {
				found = true;
				a_room->getRefCreatures().push_back(map->creatures[i]);
				break;
			}
		}
	}
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
				checkAllTriggers(user_input);
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

					if (cur_room->getContainers()[i]->getStatus() != "locked"
						&& cur_room->getContainers()[i]->opened != false) {
						for (int j = 0; j < cur_room->getContainers()[i]->getItems().size(); j++) {
							if (cur_room->getContainers()[i]->getItems()[j]->getName() == input) {
								Item* changing_item = cur_room->getContainers()[i]->getItems()[j];
								cur_room->getContainers()[i]->getRefItems().erase(cur_room->getContainers()[i]->getRefItems().begin() + j);
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
			else {
				checkAllTriggers(user_input);
			}
			
		}
	}
	else if (str_cmd == "drop") {
		if (!checkAllTriggers(user_input)) {
			bool itemFound = false;
			for (int i = 0; i < inventory.size(); i++) {
				if (inventory[i]->getName() == input) {
					Item* changing_item = inventory[i];
					inventory.erase(inventory.begin() + i);
					cur_room->getRefItems().push_back(changing_item);
					itemFound = true;
					cout << changing_item->getName() << " dropped.\n";
					break;
				}
			}
			if (!itemFound) {
				cout << "Error\n";
			}
			else {
				checkAllTriggers(user_input);
			}
		}
	}
	else if (str_cmd == "read") {
		if (!checkAllTriggers(user_input)) {
			bool itemFound = false;
			for (int i = 0; i < inventory.size(); i++) {
				if (inventory[i]->getName() == input) {
					itemFound = true;
					if (inventory[i]->writing != "") {
						cout << inventory[i]->writing << "\n";
					}
					else {
						cout << "Nothing written.\n";
					}
					break;
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
			if (input == "exit" && cur_room->type == "exit") {
				gameOver = true;
			}
			else {
				for (int i = 0; i < cur_room->getContainers().size(); i++) {
					if (cur_room->getContainers()[i]->getName() == input) {
						cout << cur_room->getContainers()[i]->getName() << " ";
						cur_room->getRefContainers()[i]->opened = true;
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
	}
	else if (str_cmd == "put" && input.size() >= 6) {
		if (!checkAllTriggers(user_input)) {
			std::string item_name = input.substr(0, input.find(" "));
			std::string place_name = input.substr(input.find("in ") + 3);
			bool found = false;
			for (int i = 0; i < inventory.size(); i++) {
				if (inventory[i]->getName() == item_name) {
					for (int j = 0; j < cur_room->getContainers().size(); j++) {
						if (cur_room->getContainers()[j]->getName() == place_name) {

							if (cur_room->getContainers()[j]->accept.size() > 0) {
								for (int k = 0; k < cur_room->getContainers()[j]->accept.size(); k++) {
									if (item_name == cur_room->getContainers()[j]->accept[k]) {
										found = true;
										cout << "Item " << item_name << " added to " << cur_room->getContainers()[j]->getName() << ".\n";
										cur_room->getContainers()[j]->getRefItems().push_back(inventory[i]);
										inventory.erase(inventory.begin() + i);
									}
								}
							}
							else {
								found = true;
								cout << "Item " << item_name << " added to " << cur_room->getContainers()[j]->getName() << ".\n";
								cur_room->getContainers()[j]->getRefItems().push_back(inventory[i]);
								inventory.erase(inventory.begin() + i);
							}
							
							break;
						}
					}
					break;
				}
			}
			if (!found) {
				cout << "Error\n";
			}
			else {
				checkAllTriggers(user_input);
			}
		}

	}
	else if (str_cmd == "attack" && input.size() >= 8) {
		if (!checkAllTriggers(user_input)) {
			bool found = false;
			std::string creature_name = input.substr(0, input.find(" "));
			std::string item_name = input.substr(input.find("with ") + 5);

			for (int i = 0; i < inventory.size(); i++) {
				if (inventory[i]->getName() == item_name) {
					found = true;
					break;
				}
			}
			if (found) {
				found = false;
				for (int i = 0; i < cur_room->getCreatures().size(); i++) {
					if (cur_room->getCreatures()[i]->getName() == creature_name) {
						for (int j = 0; j < cur_room->getCreatures()[i]->vulnerabilities.size(); j++) {
							if (cur_room->getCreatures()[i]->vulnerabilities[j] == item_name) {
								found = true;
								break;
							}
						}

						if (found) {
							bool triggered = true;
							for (int j = 0; j < cur_room->getCreatures()[i]->attk->conditions.size(); j++) {
								triggered = triggered && checkCondition(cur_room->getCreatures()[i]->attk->conditions[j]);
							}
							if (triggered) {
								std::vector<Action> temp_actions = cur_room->getCreatures()[i]->attk->actions;
								std::vector<std::string> temp_prints = cur_room->getCreatures()[i]->attk->prints;
								cout << "You assault the " << cur_room->getCreatures()[i]->getName() << " with the ";
								cout << item_name << ".\n";
						
								for (int j = 0; j < temp_prints.size(); j++) {
									cout << temp_prints[j] << "\n";
								}
								for (int j = 0; j < temp_actions.size(); j++) {
									performAction(temp_actions[j]);

								}
							}
							else {
								found = false;
							}
							break;
						}
					}
				}
			}
			
			if (!found) {
				cout << "Error\n";
			}
			else {
				checkAllTriggers(user_input);
			}
			
		}
	}
	else if (str_cmd == "turn" && input.size() > 2 && input.substr(0,2) == "on") {
		if (!checkAllTriggers(user_input)) {
			bool found = false;
			std::string item_name = user_input.substr(user_input.find("on ")+3);
			for (int i = 0; i < inventory.size(); i++) {
				if (inventory[i]->getName() == item_name && inventory[i]->hasTurnOn){
					found = true;
					cout << "You activate the " << item_name << ".\n";
					performAction(*(inventory[i]->action));
					if (inventory[i]->turnon != "") {
						cout << inventory[i]->turnon << "\n";
					}
					break;

				}
			}
			if (!found) {
				cout << "Error\n";
			}
			else {
				checkAllTriggers(user_input);
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











//Old trigger code below

/*
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
							for (int k = 0; k < inventory.size(); k++) {
								if (cur_cond.object == inventory[k]->getName() && cur_cond.status == inventory[k]->getStatus()) {
									triggered = true;
									break;
								}
							}
							if (triggered) {
								break;
							}

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
					}*/