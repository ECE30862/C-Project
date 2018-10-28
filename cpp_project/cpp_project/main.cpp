#include "Game.h"

int main(void) {
	
	Game game("sample.txt.xml");
	bool start = true;
	while (!game.gameOver) {
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
	std::cout << "Game Over!\n";
	system("PAUSE");
	return 0;
}