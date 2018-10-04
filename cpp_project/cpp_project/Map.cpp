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

	for (xml_node<> * map_node = root_node->first_node("room"); map_node; map_node = map_node->next_sibling("room"))
	{
		string a_name = map_node->first_node("name")->value();
		rooms.push_back(new Room(a_name));
	}

	for (int i = 0; i < rooms.size(); i++) {
		cout << "Room: " << rooms[i]->getName() << "\n";
	}
}

Map::~Map(){}