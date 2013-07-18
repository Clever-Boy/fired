#include "game.hpp"

int fired::Game::Init() {
	App.Create(sf::VideoMode(1024, 600, 32), PROJECT_NAME " v" PROJECT_VER);
	Running = true;
}


int fired::Game::Update() {
	ProcessEvents();

	App.Clear();
	App.Display();
}


int fired::Game::ProcessEvents() {
	sf::Event Event;
	while (App.GetEvent(Event)) ProcessEvent(Event);

	if (!App.IsOpened()) Running = false;
}


int fired::Game::ProcessEvent(sf::Event Event) {
	if (Event.Type == sf::Event::Closed) Running = false;
	return 0;
}
