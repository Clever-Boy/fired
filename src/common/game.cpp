#include "game.hpp"

//======================================================================


fired::Game::Game() {
	clock    = new sf::Clock;
	settings = new fired::Settings();

	unsigned long style;
	if (settings->window.fullScreen) style = sf::Style::Fullscreen;
	else                             style = sf::Style::Close;

	app = new sf::RenderWindow(sf::VideoMode(settings->window.width,
	                           settings->window.height,
	                           settings->window.bpp), PROJECT_CAPTION " v" PROJECT_VER, style);
	app->setMouseCursorVisible(false);

	icon = new sf::Image();
	icon->loadFromFile("data/img/gui/icon.tga");
	app->setIcon(128, 128, icon->getPixelsPtr());

	running   = true;
	focused   = true;
	gameState = gsNone;

	mouse    = new fired::Mouse();
	keyboard = new fired::Keyboard();
	handlers = new fired::Handlers();

	musicTheme = new sf::Music();
	musicTheme->setLoop(true);
	musicTheme->setVolume(settings->volume.music);

	font = new sf::Font;
	font->loadFromFile("data/fonts/batik.ttf");

	setGameState(gsStartScr);
	lastClock = clock->getElapsedTime().asMilliseconds();
}

//======================================================================


fired::Game::~Game() {
	delete musicTheme;
	delete mouse;
	delete keyboard;
	delete handlers;
	delete gameScreen;
	delete font;
	delete clock;
	delete icon;
	delete settings;
	delete app;
}

//======================================================================


void fired::Game::update() {
	long currentClock = clock->getElapsedTime().asMilliseconds();
	if (currentClock - lastClock < 10) return;

	frameClock = (currentClock - lastClock) / 1000.0;
	lastClock = currentClock;

	if (switchGameState()) return;
	processEvents();
	if (!focused) return;


	app->clear();
	gameScreen->update();
	app->display();
}

//======================================================================


void fired::Game::processHandler(fired::Handler handler) {
	(*handlers.*handler)();
}

//======================================================================


void fired::Game::generateWorld() {
	delete new fired::MapGenerator();
}

//======================================================================


void fired::Game::processEvents() {
	sf::Event event;
	while (app->pollEvent(event)) processEvent(event);

	if (!app->isOpen()) running = false;
}

//======================================================================


void fired::Game::processEvent(sf::Event event) {
	switch(event.type) {
		case sf::Event::Closed:
			running = false;
			break;

		case sf::Event::LostFocus:
			focused = false;
			break;

		case sf::Event::GainedFocus:
			focused = true;
			break;

		default:
			gameScreen->processEvent(event);
	}
}

//======================================================================


void fired::Game::setMusic(const char *musicFile) {
	musicTheme->stop();
	musicTheme->openFromFile(musicFile);
	musicTheme->play();
}

//======================================================================


void fired::Game::setGameState(fired::GameState state) {
	gameStateNew = state;
}

//======================================================================


bool fired::Game::switchGameState() {
	if (gameState == gameStateNew) return false;

	if (gameState != gsNone) {
		musicTheme->stop();
		delete gameScreen;
	}

	gameState = gameStateNew;

	if      (gameState == gsMainMenu)   gameScreen = new fired::MainMenu(mouse);
	else if (gameState == gsStartScr)   gameScreen = new fired::StartScr();
	else if (gameState == gsCreditsScr) gameScreen = new fired::CreditsScr();
	else if (gameState == gsWorld)      gameScreen = new fired::World(mouse);

	lastClock = clock->getElapsedTime().asMilliseconds();
	return true;
}
