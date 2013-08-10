#include "game.hpp"

//======================================================================


fired::Game::Game() {
	clock    = new sf::Clock;
	settings = new fired::Settings();

	unsigned long style;
	if (settings->window.fullScreen) style = sf::Style::Fullscreen;
	else                            style = sf::Style::Close;

	app = new sf::RenderWindow(sf::VideoMode(settings->window.width,
	                           settings->window.height,
	                           settings->window.bpp), PROJECT_NAME " v" PROJECT_VER, style);
	app->setMouseCursorVisible(false);

	icon = new sf::Image();
	icon->loadFromFile("data/img/gui/icon.tga");
	app->setIcon(128, 128, icon->getPixelsPtr());

	running   = true;
	focused   = true;
	gameState = gsNone;

	mouse    = new fired::Mouse(this);
	keyboard = new fired::Keyboard(this);
	handlers = new fired::Handlers(this);

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

	if      (gameState == gsMainMenu)   delete mainMenu;
	else if (gameState == gsStartScr)   delete startScr;
	else if (gameState == gsCreditsScr) delete creditsScr;
	else if (gameState == gsWorld)      delete world;

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

	if      (gameState == gsMainMenu)   mainMenu->update();
	else if (gameState == gsStartScr)   startScr->update();
	else if (gameState == gsCreditsScr) creditsScr->update();
	else if (gameState == gsWorld)      world->update();

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
			if      (gameState == gsMainMenu)   mainMenu->processEvent(event);
			else if (gameState == gsStartScr)   startScr->processEvent(event);
			else if (gameState == gsCreditsScr) creditsScr->processEvent(event);
			else if (gameState == gsWorld)      world->processEvent(event);
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
	musicTheme->stop();

	if      (gameState == gsMainMenu)   delete mainMenu;
	else if (gameState == gsStartScr)   delete startScr;
	else if (gameState == gsCreditsScr) delete creditsScr;
	else if (gameState == gsWorld)      delete world;

	gameState = gameStateNew;

	if      (gameState == gsMainMenu)   mainMenu   = new fired::MainMenu(this, mouse);
	else if (gameState == gsStartScr)   startScr   = new fired::StartScr(this);
	else if (gameState == gsCreditsScr) creditsScr = new fired::CreditsScr(this);
	else if (gameState == gsWorld)      world      = new fired::World(this);

	return true;
}
