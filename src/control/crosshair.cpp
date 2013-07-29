#include "game.hpp"
#include <math.h>


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
	crosshairCur->setOrigin(crosshairTex->getSize().x / 2, crosshairTex->getSize().y / 2);
}



void fired::Crosshair::deinit() {
	delete crosshairTex;
	delete crosshairCur;
}



void fired::Crosshair::processEvent(sf::Event event) {
	return;
}



void fired::Crosshair::update(float distance) {
	sf::Vector2f center(settings->window.width / 2, settings->window.height / 2);
	pos = sf::Vector2f(sf::Mouse::getPosition(*app));
/*
	float dist = sqrt((center.x - pos.x)*(center.x - pos.x) + (center.y - pos.y)*(center.y - pos.y));
	if (dist > distance) {
		pos = sf::Vector2f(center.x + (pos.x - center.x) * (distance / dist), center.y + (pos.y - center.y) * (distance / dist));
		sf::Mouse::setPosition(sf::Vector2i(pos), *app);
	}
*/
	render();
}



void fired::Crosshair::render() {
	crosshairCur->setPosition(pos + cam->getOffset());
	app->draw(*crosshairCur);
}
