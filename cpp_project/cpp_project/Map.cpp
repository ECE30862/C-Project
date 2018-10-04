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

	string a_name;
	while (item_node || container_node || creature_node) {
		if (item_node) {
			a_name = item_node->first_node("name")->value();
			items.push_back(new Item(a_name));
			item_node = item_node->next_sibling("item");
		}
		if (container_node) {
			a_name = container_node->first_node("name")->value();
			containers.push_back(new Container(a_name));
			container_node = container_node->next_sibling("container");
		}
		if (creature_node) {
			a_name = creature_node->first_node("name")->value();
			creatures.push_back(new Creature(a_name));
			creature_node = creature_node->next_sibling("creature");
		}
	}

	while (room_node) {
		a_name = room_node->first_node("name")->value();
		rooms.push_back(new Room(a_name));
		room_node = room_node->next_sibling("room");
	}

	for (int i = 0; i < rooms.size(); i++) {
		cout << "Room: " << rooms[i]->getName() << "\n";
	}
	for (int i = 0; i < items.size(); i++) {
		cout << "Item: " << items[i]->getName() << "\n";
	}
	for (int i = 0; i < containers.size(); i++) {
		cout << "Container: " << containers[i]->getName() << "\n";
	}
	for (int i = 0; i < creatures.size(); i++) {
		cout << "Creature: " << creatures[i]->getName() << "\n";
	}
}

Map::~Map(){}