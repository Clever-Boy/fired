#include "game.hpp"

//======================================================================


void fired::GUI::init(fired::Game *_game, fired::Camera *_cam, fired::Player *_player) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	cam      = _cam;
	player   = _player;

	barTex = new sf::Texture;
	barTex->loadFromFile("data/img/gui/world/guibar.tga");
	barSpr = new sf::Sprite;
	barSpr->setTexture(*barTex);

	healthTex = new sf::Texture;
	healthTex->loadFromFile("data/img/gui/world/health.tga");
	healthSpr = new sf::RectangleShape(sf::Vector2f(284, 27));
	healthSpr->setTexture(healthTex);

	ammoTex = new sf::Texture;
	ammoTex->loadFromFile("data/img/gui/world/ammo.tga");
	ammoSpr = new sf::Sprite;
	ammoSpr->setTexture(*ammoTex);
	ammoCnt = new sf::String;
	ammoTxt = new sf::Text;
	ammoTxt->setFont(*game->getFont());
	ammoTxt->setCharacterSize(32);

}

//======================================================================


fired::GUI::~GUI() {
	delete barSpr;
	delete barTex;

	delete healthSpr;
	delete healthTex;

	delete ammoSpr;
	delete ammoTex;
	delete ammoCnt;
	delete ammoTxt;
}

//======================================================================


void fired::GUI::update() {
	int ammo_count = player->getChar()->getAmmo();

	if (ammo_count != -1) {
		char ammo[8];
		snprintf(ammo, 8, "%u", ammo_count);
		*ammoCnt = ammo;
	} else
		*ammoCnt = "inf";

	ammoTxt->setString(*ammoCnt);

	healthSpr->setScale(player->getChar()->getHpPercent(), 1);
	render();
}

//======================================================================


void fired::GUI::render() {
	healthSpr->setPosition(cam->getOffset() + sf::Vector2f(25, 25));
	app->draw(*healthSpr);

	barSpr->setPosition(cam->getOffset() + sf::Vector2f(20, 20));
	app->draw(*barSpr);

	ammoSpr->setPosition(cam->getOffset() + sf::Vector2f(20, settings->window.height - 20 - ammoTex->getSize().y));
	app->draw(*ammoSpr);

	ammoTxt->setPosition(cam->getOffset() + sf::Vector2f(25 + ammoTex->getSize().x, settings->window.height - 20 - ammoTex->getSize().y));
	app->draw(*ammoTxt);
}
