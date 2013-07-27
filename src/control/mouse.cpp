#include "game.hpp"


void fired::Mouse::init(fired::Game *_game) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	mouseTex = new sf::Texture();
	mouseCur = new sf::Sprite();

	mouseTex->loadFromFile("data/img/gui/mainmenu/mouse.tga");
	mouseCur->setTexture(*mouseTex);
	mouseTex->setSmooth(true);
}



void fired::Mouse::deinit() {
	delete mouseTex;
	delete mouseCur;
}



void fired::Mouse::processEvent(sf::Event event) {
	return;
}



void fired::Mouse::update() {
	pos = sf::Vector2f(sf::Mouse::getPosition(*app));
	render();
}



void fired::Mouse::render() {
	mouseCur->setPosition(pos);
	app->draw(*mouseCur);
}
