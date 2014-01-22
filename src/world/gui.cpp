/***********************************************************************
     * File       : gui.cpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Class
     * constructor

***********************************************************************/
fired::GUI::GUI(fired::Player *_player) {
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
	txt->setFont(*game->font);
	txt->setCharacterSize(12);

}



/***********************************************************************
     * Class
     * destructor

***********************************************************************/
fired::GUI::~GUI() {
	delete barSpr;
	delete barTex;

	delete bar;
	delete str;
	delete txt;
}



/***********************************************************************
     * Class
     * update

***********************************************************************/
void fired::GUI::update() {
	render();
}



/***********************************************************************
     * Class
     * render

***********************************************************************/
void fired::GUI::render() {
	barSpr->setPosition(sf::Vector2f(20, settings->window.height - barHeight - 20));
	app->draw(*barSpr);

	barSpr->setPosition(sf::Vector2f(settings->window.width - barWidth - 20, settings->window.height - barHeight - 20));
	app->draw(*barSpr);


	// Health bar
	bar->setSize(sf::Vector2f(200, 12));
	bar->setFillColor(sf::Color(75, 0, 0, 255));
	bar->setPosition(sf::Vector2f(23, settings->window.height - barHeight - 17));
	app->draw(*bar);

	bar->setSize(sf::Vector2f(200 * player->character->getHpPercent(), 12));
	bar->setFillColor(sf::Color(150, 0, 0, 255));
	app->draw(*bar);

	*str = player->character->getHpString();
	txt->setString(*str);
	txt->setPosition(sf::Vector2f(23 + (barWidth - txt->getGlobalBounds().width) / 2.0f, settings->window.height - barHeight - 19));
	app->draw(*txt);


	// XP bar
	bar->setSize(sf::Vector2f(200, 12));
	bar->setFillColor(sf::Color(75, 75, 0, 255));
	bar->setPosition(sf::Vector2f(23, settings->window.height - barHeight - 2));
	app->draw(*bar);

	bar->setSize(sf::Vector2f(200 * player->character->getXpPercent(), 12));
	bar->setFillColor(sf::Color(150, 150, 0, 255));
	app->draw(*bar);

	*str = player->character->getXpString();
	txt->setString(*str);
	txt->setPosition(sf::Vector2f(23 + (barWidth - txt->getGlobalBounds().width) / 2.0f, settings->window.height - barHeight - 4));
	app->draw(*txt);


	// Ammo bar
	bar->setSize(sf::Vector2f(200, 12));
	bar->setFillColor(sf::Color(0, 75, 0, 255));
	bar->setPosition(sf::Vector2f(settings->window.width - barWidth - 17, settings->window.height - barHeight - 17));
	app->draw(*bar);

	bar->setSize(sf::Vector2f(200 * player->character->getAmmoPercent(), 12));
	bar->setFillColor(sf::Color(0, 150, 0, 255));
	app->draw(*bar);

	*str = player->character->getAmmoString();
	txt->setString(*str);
	txt->setPosition(sf::Vector2f(settings->window.width - barWidth - 17 + (barWidth - txt->getGlobalBounds().width) / 2.0f, settings->window.height - barHeight - 19));
	app->draw(*txt);


	// Cooldown bar
	bar->setSize(sf::Vector2f(200, 12));
	bar->setFillColor(sf::Color(75, 30, 0, 255));
	bar->setPosition(sf::Vector2f(settings->window.width - barWidth - 17, settings->window.height - barHeight - 2));
	app->draw(*bar);

	bar->setSize(sf::Vector2f(200 * player->character->getCooldownPercent(), 12));
	bar->setFillColor(sf::Color(150, 60, 0, 255));
	app->draw(*bar);

	*str = player->character->getCooldownString();
	txt->setString(*str);
	txt->setPosition(sf::Vector2f(settings->window.width - barWidth - 17 + (barWidth - txt->getGlobalBounds().width) / 2.0f, settings->window.height - barHeight - 4));
	app->draw(*txt);
}
