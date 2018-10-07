#include "Map.h"

Map::Map(std::string filename) {
	using namespace rapidxml;
	using namespace std;
	xml_document<> doc;

	ifstream xml_file("sample.txt.xml");
	vector<char> buffer((istreambuf_iterator<char>(xml_file)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	doc.parse<0>(&buffer[0]);

	xml_node<> * root_node;
	root_node = doc.first_node("map");

	xml_node<> * item_node = root_node->first_node("item");
	xml_node<> * container_node = root_node->first_node("container");
	xml_node<> * creature_node = root_node->first_node("creature");
	xml_node<> * room_node = root_node->first_node("room");

	while (item_node || container_node || creature_node) {
		if (item_node) {
			items.push_back(new Item(item_node));
			item_node = item_node->next_sibling("item");
		}
		if (container_node) {
			containers.push_back(new Container(container_node));
			container_node = container_node->next_sibling("container");
		}
		if (creature_node) {
			creatures.push_back(new Creature(creature_node));
			creature_node = creature_node->next_sibling("creature");
		}
	}

	while (room_node) {
		rooms.push_back(new Room(room_node));
		room_node = room_node->next_sibling("room");
	}

	printLists();
}

Map::~Map(){}


void Map::printLists() const {
	using namespace std;
	for (int i = 0; i < rooms.size(); i++) {
		cout << "Room: " << rooms[i]->getName() << ", " << rooms[i]->getStatus() << ", " << rooms[i]->getDescription() << "\n";
	}
	for (int i = 0; i < items.size(); i++) {
		cout << "Item: " << items[i]->getName() << ", " << items[i]->getStatus() << ", " << items[i]->getDescription() << "\n";
	}
	for (int i = 0; i < containers.size(); i++) {
		cout << "Container: " << containers[i]->getName() << ", " << containers[i]->getStatus() << ", " << containers[i]->getDescription() << "\n";
	}
	for (int i = 0; i < creatures.size(); i++) {
		cout << "Creature: " << creatures[i]->getName() << ", " << creatures[i]->getStatus() << ", " << creatures[i]->getDescription() << "\n";
	}
}