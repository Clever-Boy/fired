#include "game.hpp"

void fired::Game::Init() {
	App.Create(sf::VideoMode(640, 480, 32), PROJECT_NAME " v" PROJECT_VER);
	Running = true;

	Mouse.Init();
	Keyboard.Init();

	MainMenu.Init();
}


void fired::Game::Update() {
	ProcessEvents();

	App.Clear();
	App.Display();
}


void fired::Game::ProcessEvents() {
	sf::Event Event;
	while (App.GetEvent(Event)) ProcessEvent(Event);

	if (!App.IsOpened()) Running = false;
}


void fired::Game::ProcessEvent(sf::Event Event) {
	if (Event.Type == sf::Event::Closed) Running = false;
}
