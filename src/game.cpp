#include "game.hpp"

void fired::Game::Init() {
	App.Create(sf::VideoMode(800, 600, 32), PROJECT_NAME " v" PROJECT_VER);
	Running = true;

	Mouse.Init(this);
	Keyboard.Init(this);
	MainMenu.Init(this);

	LastClock = Clock.GetElapsedTime();
}


void fired::Game::Update() {
	float CurrentClock = Clock.GetElapsedTime();
	FrameClock = CurrentClock - LastClock;
	LastClock = CurrentClock;

	ProcessEvents();
	App.Clear();

	MainMenu.Update(FrameClock);
	Mouse.Update(FrameClock);

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
