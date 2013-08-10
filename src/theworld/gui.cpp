#include "game.hpp"

//======================================================================


fired::GUI::GUI(fired::Game *_game, fired::Camera *_cam, fired::Player *_player) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	cam      = _cam;
	player   = _player;

	barTex = new sf::Texture;
	barTex->loadFromFile("data/img/gui/world/guibar.tga");
	barSpr = new sf::Sprite;
	barSpr->setTexture(*barTex);

	barWidth  = barTex->getSize().x;
	barHeight = barTex->getSize().y;
	bar = new sf::RectangleShape();

	str = new sf::String;
	txt = new sf::Text;
	txt->setFont(*game->getFont());
	txt->setCharacterSize(12);

}

//======================================================================


fired::GUI::~GUI() {
	delete barSpr;
	delete barTex;

	delete bar;
	delete str;
	delete txt;
}

//======================================================================


void fired::GUI::update() {
	render();
}

//======================================================================


void fired::GUI::render() {
	barSpr->setPosition(cam->getOffset() + sf::Vector2f(20, settings->window.height - barHeight - 20));
	app->draw(*barSpr);

	barSpr->setPosition(cam->getOffset() + sf::Vector2f(settings->window.width - barWidth - 20, settings->window.height - barHeight - 20));
	app->draw(*barSpr);


	// Health bar
	bar->setSize(sf::Vector2f(200, 12));
	bar->setFillColor(sf::Color(75, 0, 0, 255));
	bar->setPosition(cam->getOffset() + sf::Vector2f(23, settings->window.height - barHeight - 17));
	app->draw(*bar);

	bar->setSize(sf::Vector2f(200 * player->getChar()->getHpPercent(), 12));
	bar->setFillColor(sf::Color(150, 0, 0, 255));
	app->draw(*bar);

	*str = player->getChar()->getHpString();
	txt->setString(*str);
	txt->setPosition(cam->getOffset() + sf::Vector2f(23 + (barWidth - txt->getGlobalBounds().width) / 2.0f, settings->window.height - barHeight - 19));
	app->draw(*txt);


	// XP bar
	bar->setSize(sf::Vector2f(200, 12));
	bar->setFillColor(sf::Color(75, 75, 0, 255));
	bar->setPosition(cam->getOffset() + sf::Vector2f(23, settings->window.height - barHeight - 2));
	app->draw(*bar);

	bar->setSize(sf::Vector2f(200 * 0.1 /*player->getChar()->getXpPercent()*/, 12));
	bar->setFillColor(sf::Color(150, 150, 0, 255));
	app->draw(*bar);

	*str = "Level 1  (10 / 100)"; //player->getChar()->getXpString();
	txt->setString(*str);
	txt->setPosition(cam->getOffset() + sf::Vector2f(23 + (barWidth - txt->getGlobalBounds().width) / 2.0f, settings->window.height - barHeight - 4));
	app->draw(*txt);


	// Ammo bar
	bar->setSize(sf::Vector2f(200, 12));
	bar->setFillColor(sf::Color(0, 75, 0, 255));
	bar->setPosition(cam->getOffset() + sf::Vector2f(settings->window.width - barWidth - 17, settings->window.height - barHeight - 17));
	app->draw(*bar);

	bar->setSize(sf::Vector2f(200 * player->getChar()->getAmmoPercent(), 12));
	bar->setFillColor(sf::Color(0, 150, 0, 255));
	app->draw(*bar);

	*str = player->getChar()->getAmmoString();
	txt->setString(*str);
	txt->setPosition(cam->getOffset() + sf::Vector2f(settings->window.width - barWidth - 17 + (barWidth - txt->getGlobalBounds().width) / 2.0f, settings->window.height - barHeight - 19));
	app->draw(*txt);


	// Cooldown bar
	bar->setSize(sf::Vector2f(200, 12));
	bar->setFillColor(sf::Color(75, 30, 0, 255));
	bar->setPosition(cam->getOffset() + sf::Vector2f(settings->window.width - barWidth - 17, settings->window.height - barHeight - 2));
	app->draw(*bar);

	bar->setSize(sf::Vector2f(200 * player->getChar()->getCooldownPercent(), 12));
	bar->setFillColor(sf::Color(150, 60, 0, 255));
	app->draw(*bar);

	*str = player->getChar()->getCooldownString();
	txt->setString(*str);
	txt->setPosition(cam->getOffset() + sf::Vector2f(settings->window.width - barWidth - 17 + (barWidth - txt->getGlobalBounds().width) / 2.0f, settings->window.height - barHeight - 4));
	app->draw(*txt);
/*
	ammoSpr->setPosition(cam->getOffset() + sf::Vector2f(20, settings->window.height - 20 - ammoTex->getSize().y));
	app->draw(*ammoSpr);

	ammoTxt->setPosition(cam->getOffset() + sf::Vector2f(25 + ammoTex->getSize().x, settings->window.height - 20 - ammoTex->getSize().y));
	app->draw(*ammoTxt);
*/
}
