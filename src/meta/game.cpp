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
	resources = new fired::Resources();

	createWindow();

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
	musicTheme->setPosition(0.0f, 0.0f, 0.0f);
	musicTheme->setRelativeToListener(true);

	setGameState(gsLoadingScr);
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
     * applySoundSettings

***********************************************************************/
void fired::Game::applySoundSettings() {
	musicTheme->setVolume(settings->volume.music);
	gameScreen->applySoundSettings();
	resources->applySoundSettings();

	settings->save();
}



/***********************************************************************
     * Game
     * applyVideoSettings

***********************************************************************/
void fired::Game::applyVideoSettings() {
	settings->save();
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
     * generateBiome

***********************************************************************/
void fired::Game::generateBiome(const char *biome, fired::WorldProperties worldProps) {
	delete new fired::MapGenerator(container->getBiome(biome), worldProps, "data/maps/test.map");
}



/***********************************************************************
     * Game
     * generateWorld

***********************************************************************/
void fired::Game::generateWorld(const char *name) {
	char worldDir[256];
	struct stat buf;
	if (stat("data/worlds", &buf) == -1) MKDIR("data/worlds");


	snprintf(worldDir, sizeof(worldDir), "data/worlds/%s", name);
	MKDIR(worldDir);

	snprintf(worldDir, sizeof(worldDir), "data/worlds/%s/players", name);
	MKDIR(worldDir);

	snprintf(worldDir, sizeof(worldDir), "data/worlds/%s/maps", name);
	MKDIR(worldDir);

	snprintf(worldDir, sizeof(worldDir), "data/worlds/%s/city.map", name);
	delete new fired::MapGenerator(container->getBiome("LocationCity"), worldDir);
}



/***********************************************************************
     * Game
     * generatePlayer

***********************************************************************/
void fired::Game::generatePlayer(const char *name, const char *worldname) {
	char playerDir[256];
	snprintf(playerDir, sizeof(playerDir), "data/worlds/%s/players/%s", worldname, name);
	MKDIR(playerDir);

	snprintf(playerDir, sizeof(playerDir), "data/worlds/%s/players/%s/home.map", worldname, name);
	delete new fired::MapGenerator(container->getBiome("LocationHome"), playerDir);

	snprintf(playerDir, sizeof(playerDir), "data/worlds/%s/players/%s/player.chr", worldname, name);
	genChar(playerDir);
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
	else if (gameState == gsLoadingScr) gameScreen = new fired::LoadingScr();
	else if (gameState == gsStartScr)   gameScreen = new fired::StartScr();
	else if (gameState == gsCreditsScr) gameScreen = new fired::CreditsScr();
	else if (gameState == gsWorld)      gameScreen = new fired::World(mouse);

	lastClock = clock->getElapsedTime().asMilliseconds();
	return true;
}
