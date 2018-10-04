#include "Map.h"

int main(void) {
	
	Map a_map("sample.txt.xml");

	while (1) {
		std::string user_input;
		std::cout << "Type 'exit' to quit\n";
		std::cin >> user_input;
		if(user_input == "exit")
			break;
	}
	return 0;
}