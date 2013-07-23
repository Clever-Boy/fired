#include "game.hpp"

void fired::Game::init() {
	settings.init();

	unsigned long style;
	if (settings.window.fullScreen) style = sf::Style::Fullscreen;
	else style = sf::Style::Close;

	app.create(sf::VideoMode(settings.window.width,
	                         settings.window.height,
	                         settings.window.bpp), PROJECT_NAME " v" PROJECT_VER, style);
	app.setMouseCursorVisible(false);
	running = true;

	mouse.init(this);
	keyboard.init(this);

	font.loadFromFile("data/fonts/advanced_pixel-7.ttf");
	setGameState(gsStartScr);
	lastClock = clock.getElapsedTime().asMilliseconds();
}


void fired::Game::update() {
	long currentClock = clock.getElapsedTime().asMilliseconds();
	if (currentClock - lastClock < 10) return;

	frameClock = (currentClock - lastClock) / 1000.0;
	lastClock = currentClock;

	processEvents();
	app.clear();

	if      (gameState == gsMainMenu)   mainMenu.update(frameClock);
	else if (gameState == gsStartScr)   startScr.update(frameClock);
	else if (gameState == gsCreditsScr) creditsScr.update(frameClock);

	app.display();
}


void fired::Game::processEvents() {
	sf::Event event;
	while (app.pollEvent(event)) processEvent(event);

	if (!app.isOpen()) running = false;
}


void fired::Game::processEvent(sf::Event event) {
	if (event.type == sf::Event::Closed) {
		running = false;
		return;
	}


	if      (gameState == gsMainMenu)   mainMenu.processEvent(event);
	else if (gameState == gsStartScr)   startScr.processEvent(event);
	else if (gameState == gsCreditsScr) creditsScr.processEvent(event);
}


void fired::Game::setGameState(fired::GameState state) {
	if      (gameState == gsMainMenu)   mainMenu.deinit();
	else if (gameState == gsStartScr)   startScr.deinit();
	else if (gameState == gsCreditsScr) creditsScr.deinit();

	gameState = state;

	if      (gameState == gsMainMenu)   mainMenu.init(this);
	else if (gameState == gsStartScr)   startScr.init(this);
	else if (gameState == gsCreditsScr) creditsScr.init(this);
}
