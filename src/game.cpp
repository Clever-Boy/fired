#include "game.hpp"

void fired::Game::init() {
	app.create(sf::VideoMode(800, 600, 32), PROJECT_NAME " v" PROJECT_VER);
	running = true;

	mouse.init(this);
	keyboard.init(this);
	mainMenu.init(this);

	lastClock = clock.getElapsedTime().asSeconds();
}


void fired::Game::update() {
	float currentClock = clock.getElapsedTime().asSeconds();
	frameClock = currentClock - lastClock;
	lastClock = currentClock;

	processEvents();
	app.clear();

	mainMenu.update(frameClock);
	mouse.update(frameClock);

	app.display();
}


void fired::Game::processEvents() {
	sf::Event event;
	while (app.pollEvent(event)) processEvent(event);

	if (!app.isOpen()) running = false;
}


void fired::Game::processEvent(sf::Event event) {
	if (event.type == sf::Event::Closed) running = false;
}
