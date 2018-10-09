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

void Game::command(std::string user_input) {
	using namespace std;
	string str_cmd = user_input.substr(0, user_input.find(" "));
	user_input = user_input.erase(0, user_input.find(" ") + 1);
	if (str_cmd == "n" || str_cmd == "s" || str_cmd == "w" || str_cmd == "e") {
		if (cur_room->getBorder(str_cmd)) {
			cur_room = cur_room->getBorder(str_cmd);
			printCurRoom();
		}
		else {
			cout << "You can't go that way.\n";
		}
	}
	else {
		cout << "Err\n";
	}
}