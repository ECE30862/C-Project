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

	//initializing the lists
	while (item_node || container_node || creature_node || room_node) {
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
		if (room_node) {
			rooms.push_back(new Room(room_node));
			room_node = room_node->next_sibling("room");
		}
	}

	//linking them together
	xml_node<> * room_creature_node;
	xml_node<> * room_container_node;
	xml_node<> * room_item_node;
	xml_node<> * room_border_node;
	xml_node<> * container_item_node;
	container_node = root_node->first_node("container");
	room_node = root_node->first_node("room");
	int room_idx = 0;
	int container_idx = 0;
	while (container_node || room_node) {
		if (room_node) {
			Room* cur_room = rooms[room_idx];
			room_idx++;
			std::vector<Item*> room_items = cur_room->getRefItems();
			std::vector<Container*> room_containers = cur_room->getRefContainers();
			Room** room_borders = cur_room->getRefBorders();
			std::vector<Creature*> room_creatures = cur_room->getRefCreatures();

			room_creature_node = room_node->first_node("creature");
			room_container_node = room_node->first_node("container");
			room_item_node = room_node->first_node("item");
			room_border_node = room_node->first_node("border");

			while (room_item_node || room_container_node || room_creature_node || room_border_node) {
				if (room_item_node) {
					for (int i = 0; i < items.size(); i++) {
						if (items[i]->getName() == room_item_node->value()) {
							room_items.push_back(items[i]);
							break;
						}
					}
					room_item_node = room_item_node->next_sibling("item");
				}
				if (room_container_node) {
					for (int i = 0; i < containers.size(); i++) {
						if (containers[i]->getName() == room_container_node->value()) {
							room_containers.push_back(containers[i]);
							break;
						}
					}
					room_container_node = room_container_node->next_sibling("container");
				}
				if (room_creature_node) {
					for (int i = 0; i < creatures.size(); i++) {
						if (creatures[i]->getName() == room_creature_node->value()) {
							room_creatures.push_back(creatures[i]);
							break;
						}
					}
					room_creature_node = room_creature_node->next_sibling("creature");
				}
				if (room_border_node) {
					for (int i = 0; i < rooms.size(); i++) {
						if (rooms[i]->getName() == room_border_node->first_node("name")->value()) {
							if ((string)room_border_node->first_node("direction")->value() == "north") {
								room_borders[0] = rooms[i];
							}
							else if ((string)room_border_node->first_node("direction")->value() == "south") {
								room_borders[1] = rooms[i];
							}
							else if ((string)room_border_node->first_node("direction")->value() == "west") {
								room_borders[2] = rooms[i];
							}
							else if ((string)room_border_node->first_node("direction")->value() == "east") {
								room_borders[3] = rooms[i];
							}
							break;
						}
					}
					room_border_node = room_border_node->next_sibling("border");
				}

			}

			room_node = room_node->next_sibling("room");
		}
		if (container_node) {
			Container* cur_container = containers[container_idx];
			container_idx++;

			std::vector<Item*> container_items = cur_container->getRefItems();
			container_item_node = container_node->first_node("item");

			while (container_item_node) {
				for (int i = 0; i < items.size(); i++) {
					if (items[i]->getName() == container_item_node->value()) {
						container_items.push_back(items[i]);
						break;
					}
				}
				container_item_node = container_item_node->next_sibling("item");
			}

			container_node = container_node->next_sibling("container");
		}
	}
	

	//printLists();
}

Map::~Map(){}


void Map::printLists() const {
	using namespace std;
	for (int i = 0; i < rooms.size(); i++) {
		cout << "Room: " << rooms[i]->getName() << "\n";
	}
	for (int i = 0; i < items.size(); i++) {
		//cout << "Item: " << items[i]->getName() << "\n";
		items[i]->printItem();
	}
	for (int i = 0; i < containers.size(); i++) {
		cout << "Container: " << containers[i]->getName() << "\n";
	}
	for (int i = 0; i < creatures.size(); i++) {
		cout << "Creature: " << creatures[i]->getName() << "\n";
	}
}

Room* Map::getEntrance() const {
	for (int i = 0; i < rooms.size(); i++) {
		if (rooms[i]->getName() == "Entrance") {
			return rooms[i];
		}
	}
	return NULL;
}