#include "Game.h"

int main(void) {
	
	Game game("sample.txt.xml");

	while (1) {
		//Main game loop

		std::string user_input;
		std::cout << "Type 'exit' to quit\n";
		std::cin >> user_input;
		if(user_input == "exit")
			break;
	}
	return 0;
}