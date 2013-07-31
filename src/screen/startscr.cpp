#include "game.hpp"

//======================================================================


void fired::StartScr::init(fired::Game *_game) {
	game       = _game;
	settings   = game->getSettings();
	app        = game->getApp();
	timeOffset = 0;
	index      = 0;

	game->setMusic("data/snd/themes/startscr.ogg");

	textures.push_back(new sf::Texture()); textures.back()->loadFromFile("data/img/gui/startscr/01.jpg");
	textures.push_back(new sf::Texture()); textures.back()->loadFromFile("data/img/gui/startscr/02.jpg");
	textures.push_back(new sf::Texture()); textures.back()->loadFromFile("data/img/gui/startscr/03.jpg");


	for (int i = 0; i < textures.size(); i++) {
		sprites.push_back(new sf::Sprite());
		sprites[i]->setTexture(*textures[i]);
		sprites[i]->move((settings->window.width - textures[i]->getSize().x) / 2, (settings->window.height - textures[i]->getSize().y) / 2);
	}
}

//======================================================================


void fired::StartScr::deinit() {
	for (int i = 0; i < textures.size(); delete sprites[i], delete textures[i], i++);
}

//======================================================================


void fired::StartScr::update() {
	timeOffset += frameClock;
	if (timeOffset > STARTSCR_TIME_DELAY) {
		index++;
		timeOffset -= STARTSCR_TIME_DELAY;
	}

	if (index == sprites.size()) {
		game->setGameState(gsMainMenu);
		return;
	}

	if      (timeOffset < STARTSCR_TIME_APPEAR)    sprites[index]->setColor(sf::Color(255, 255, 255, 255 * timeOffset / STARTSCR_TIME_APPEAR));
	else if (timeOffset < STARTSCR_TIME_DISAPPEAR) sprites[index]->setColor(sf::Color(255, 255, 255, 255));
	else                                           sprites[index]->setColor(sf::Color(255, 255, 255, 255 * (STARTSCR_TIME_DELAY - timeOffset) / (STARTSCR_TIME_DELAY - STARTSCR_TIME_DISAPPEAR)));

	render();
}

//======================================================================


void fired::StartScr::render() {
	app->draw(*sprites[index]);
}

//======================================================================


void fired::StartScr::processEvent(sf::Event event) {
	if ((event.type == sf::Event::MouseButtonReleased) ||
	    (event.type == sf::Event::KeyPressed)) {
		timeOffset = 0;
		index++;
	}
}
