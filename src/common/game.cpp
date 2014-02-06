/***********************************************************************
     * File       : game.cpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Game
     * constructor

***********************************************************************/
fired::Game::Game() {
	clock     = new sf::Clock;
	settings  = new fired::Settings();
	container = new fired::Container();
	resources = new fired::Resources();

	unsigned long style;
	if (settings->window.fullScreen) style = sf::Style::Fullscreen;
	else                             style = sf::Style::Close;

	sf::ContextSettings contextSettings;
	contextSettings.antialiasingLevel = settings->window.antialiasing;

	app = new sf::RenderWindow(sf::VideoMode(settings->window.width,
	                           settings->window.height,
	                           settings->window.bpp),
	                           PROJECT_CAPTION " v" PROJECT_VER,
	                           style,
	                           contextSettings);
	app->setMouseCursorVisible(false);

	icon = new sf::Image();
	icon->loadFromFile("data/img/gui/icon.png");
	app->setIcon(128, 128, icon->getPixelsPtr());

	running   = true;
	focused   = true;
	gameState = gsNone;

	mouse    = new fired::Mouse();
	handlers = new fired::Handlers();

	musicTheme = new sf::Music();
	musicTheme->setLoop(true);
	musicTheme->setVolume(settings->volume.music);

	font = new sf::Font;
	font->loadFromFile("data/fonts/batik.ttf");

	setGameState(gsStartScr);
	lastClock = clock->getElapsedTime().asMilliseconds();
}



/***********************************************************************
     * Game
     * destructor

***********************************************************************/
fired::Game::~Game() {
	delete musicTheme;
	delete mouse;
	delete handlers;
	delete gameScreen;
	delete font;
	delete clock;
	delete icon;
	delete settings;
	delete container;
	delete resources;
	delete app;
}



/***********************************************************************
     * Game
     * update

***********************************************************************/
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



/***********************************************************************
     * Game
     * processHandler

***********************************************************************/
void fired::Game::processHandler(fired::Handler handler) {
	(*handlers.*handler)();
}



/***********************************************************************
     * Game
     * generateWorld

***********************************************************************/
void fired::Game::generateWorld() {
	delete new fired::MapGenerator(container->getBiome("City"));
}



/***********************************************************************
     * Game
     * processEvents

***********************************************************************/
void fired::Game::processEvents() {
	sf::Event event;
	while (app->pollEvent(event)) processEvent(event);

	if (!app->isOpen()) running = false;
}



/***********************************************************************
     * Game
     * processEvent

***********************************************************************/
void fired::Game::processEvent(sf::Event event) {
	switch(event.type) {
		case sf::Event::Closed:
			stop();
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



/***********************************************************************
     * Game
     * setMusic

***********************************************************************/
void fired::Game::setMusic(const char *musicFile) {
	musicTheme->stop();
	musicTheme->openFromFile(musicFile);
	musicTheme->play();
}



/***********************************************************************
     * Game
     * setGameState

***********************************************************************/
void fired::Game::setGameState(fired::GameState state) {
	gameStateNew = state;
}



/***********************************************************************
     * Game
     * switchGameState

***********************************************************************/
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
