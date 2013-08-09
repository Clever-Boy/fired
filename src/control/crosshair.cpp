#include "game.hpp"

//======================================================================


void fired::Crosshair::init(fired::Game *_game, fired::Camera *_cam, fired::Phys *_owner) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	cam      = _cam;
	owner    = _owner;

	crosshairTex = new sf::Texture();
	crosshairCur = new sf::Sprite();

	crosshairTex->loadFromFile("data/img/gui/world/crosshair.tga");
	crosshairCur->setTexture(*crosshairTex);
	crosshairTex->setSmooth(true);
	crosshairCur->setOrigin(crosshairTex->getSize().x / 2, crosshairTex->getSize().y / 2);
}

//======================================================================


void fired::Crosshair::deinit() {
	delete crosshairTex;
	delete crosshairCur;
}

//======================================================================


void fired::Crosshair::update(float distance) {
	sf::Vector2f center(settings->window.width / 2, settings->window.height / 2);
	center -= (cam->getOffset() + center - owner->center);
	pos = sf::Vector2f(sf::Mouse::getPosition(*app));

	float dist = vLen(center - pos);
	if (dist > distance) {
		pos = sf::Vector2f(center.x + (pos.x - center.x) * (distance / dist), center.y + (pos.y - center.y) * (distance / dist));
		sf::Mouse::setPosition(sf::Vector2i(pos), *app);
	}

	angle = atan2(pos.y + cam->getOffset().y - owner->center.y, pos.x + cam->getOffset().x - owner->center.x);
	render();
}

//======================================================================


void fired::Crosshair::render() {
	crosshairCur->setPosition(pos + cam->getOffset());
	app->draw(*crosshairCur);
}
