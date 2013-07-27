#include "game.hpp"


void fired::Crosshair::init(fired::Game *_game, fired::Camera *_cam) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	cam      = _cam;

	crosshairTex = new sf::Texture();
	crosshairCur = new sf::Sprite();

	crosshairTex->loadFromFile("data/img/gui/world/crosshair.tga");
	crosshairCur->setTexture(*crosshairTex);
	crosshairTex->setSmooth(true);
}



void fired::Crosshair::deinit() {
	delete crosshairTex;
	delete crosshairCur;
}



void fired::Crosshair::processEvent(sf::Event event) {
	return;
}



void fired::Crosshair::update() {
	pos = sf::Vector2f(sf::Mouse::getPosition(*app));
	render();
}



void fired::Crosshair::render() {
	crosshairCur->setPosition(pos + cam->getOffset());
	app->draw(*crosshairCur);
}
