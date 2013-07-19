#include "game.hpp"

void fired::Game::init() {
	settings.window.width      = 800;
	settings.window.height     = 600;
	settings.window.bpp        = 32;
	settings.window.fullScreen = false;

	unsigned long style;
	if (settings.window.fullScreen) style = sf::Style::Fullscreen;
	else style = sf::Style::Close;

	app.create(sf::VideoMode(settings.window.width,
	                         settings.window.height,
	                         settings.window.bpp), PROJECT_NAME " v" PROJECT_VER, style);
	running = true;

	mouse.init(this);
	keyboard.init(this);
	mainMenu.init(this);

	lastClock = clock.getElapsedTime().asMilliseconds();
}


void fired::Game::update() {
	long currentClock = clock.getElapsedTime().asMilliseconds();
	if (currentClock - lastClock < 10) return;

	frameClock = (currentClock - lastClock) / 1000.0;
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
