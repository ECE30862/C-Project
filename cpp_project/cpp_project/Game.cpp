#include "Game.h"

Game::Game(std::string filename) {
	map = new Map(filename);
}

Game::~Game() {
	delete map;
}