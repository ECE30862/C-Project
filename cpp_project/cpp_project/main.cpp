#include "Game.h"

int main(void) {
	
	Game game("sample.txt.xml");
	bool start = true;
	while (1) {
		//Main game loop
		if (start) {
			game.printCurRoom();
			start = false;
		}
		std::string user_input;
		getline(std::cin, user_input);
		if (user_input == "quit") {
			break;
		}
		else {
			game.command(user_input);
		}
	}
	return 0;
}