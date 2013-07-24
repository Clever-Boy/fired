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

	running   = true;
	gameState = gsNone;

	mouse.init(this);
	keyboard.init(this);
	handlers.init(this);

	musicTheme.setLoop(true);
	musicTheme.setVolume(settings.volume.music);

	font.loadFromFile("data/fonts/advanced_pixel-7.ttf");
	setGameState(gsStartScr);
	lastClock = clock.getElapsedTime().asMilliseconds();
}



void fired::Game::deinit() {
	musicTheme.stop();
	mouse.deinit();

	if      (gameState == gsMainMenu)   mainMenu.deinit();
	else if (gameState == gsStartScr)   startScr.deinit();
	else if (gameState == gsCreditsScr) creditsScr.deinit();
	else if (gameState == gsWorld)      world.deinit();
}



void fired::Game::update() {
	long currentClock = clock.getElapsedTime().asMilliseconds();
	if (currentClock - lastClock < 10) return;

	frameClock = (currentClock - lastClock) / 1000.0;
	lastClock = currentClock;

	switchGameState();
	processEvents();
	app.clear();

	if      (gameState == gsMainMenu)   mainMenu.update(frameClock);
	else if (gameState == gsStartScr)   startScr.update(frameClock);
	else if (gameState == gsCreditsScr) creditsScr.update(frameClock);
	else if (gameState == gsWorld)      world.update(frameClock);

	app.display();
}



void fired::Game::processHandler(fired::Handler handler) {
	(handlers.*handler)();
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
	else if (gameState == gsWorld)      world.processEvent(event);
}



void fired::Game::setMusic(const char *musicFile) {
	musicTheme.stop();
	musicTheme.openFromFile(musicFile);
	musicTheme.play();
}



void fired::Game::setGameState(fired::GameState state) {
	gameStateNew = state;
}



void fired::Game::switchGameState() {
	if (gameState == gameStateNew) return;
	musicTheme.stop();

	if      (gameState == gsMainMenu)   mainMenu.deinit();
	else if (gameState == gsStartScr)   startScr.deinit();
	else if (gameState == gsCreditsScr) creditsScr.deinit();
	else if (gameState == gsWorld)      world.deinit();

	gameState = gameStateNew;

	if      (gameState == gsMainMenu)   mainMenu.init(this, &mouse);
	else if (gameState == gsStartScr)   startScr.init(this);
	else if (gameState == gsCreditsScr) creditsScr.init(this);
	else if (gameState == gsWorld)      world.init(this);
}
