/***********************************************************************
     * File       : world_gui.cpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Class
     * constructor

***********************************************************************/
fired::GUI::GUI(fired::Character *_owner) {
	owner  = _owner;

	barTex = new sf::Texture;
	barTex->loadFromFile("data/img/gui/world/guibar.png");
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
	float percent;
	char outStr[64];

	barSpr->setPosition(sf::Vector2f(20, settings->window.height - barHeight - 20));
	app->draw(*barSpr);

	barSpr->setPosition(sf::Vector2f(settings->window.width - barWidth - 20, settings->window.height - barHeight - 20));
	app->draw(*barSpr);


	// Health bar
	bar->setSize(sf::Vector2f(200, 12));
	bar->setFillColor(sf::Color(75, 0, 0, 255));
	bar->setPosition(sf::Vector2f(23, settings->window.height - barHeight - 17));
	app->draw(*bar);


	if (owner->baseStats.HP > 0) percent = (float)owner->baseStats.HP / (float)owner->baseStats.maxHP;
	else                          percent = 0.0f;

	bar->setSize(sf::Vector2f(200 * percent, 12));
	bar->setFillColor(sf::Color(150, 0, 0, 255));
	app->draw(*bar);


	snprintf(outStr, sizeof(outStr), "HP  %d / %d", owner->baseStats.HP, owner->baseStats.maxHP);
	*str = std::string(outStr);
	txt->setString(*str);
	txt->setPosition(sf::Vector2f(23 + (barWidth - txt->getGlobalBounds().width) / 2.0f, settings->window.height - barHeight - 19));
	app->draw(*txt);


	// XP bar
	bar->setSize(sf::Vector2f(200, 12));
	bar->setFillColor(sf::Color(75, 75, 0, 255));
	bar->setPosition(sf::Vector2f(23, settings->window.height - barHeight - 2));
	app->draw(*bar);


	percent = (float)(owner->XP - owner->lastXP) / (float)(owner->needXP - owner->lastXP);
	bar->setSize(sf::Vector2f(200 * percent, 12));
	bar->setFillColor(sf::Color(150, 150, 0, 255));
	app->draw(*bar);


	snprintf(outStr, sizeof(outStr), "Level %u  (%lu / %lu)", owner->level, owner->XP, owner->needXP);
	*str = std::string(outStr);
	txt->setString(*str);
	txt->setPosition(sf::Vector2f(23 + (barWidth - txt->getGlobalBounds().width) / 2.0f, settings->window.height - barHeight - 4));
	app->draw(*txt);


	// Ammo bar
	bar->setSize(sf::Vector2f(200, 12));
	bar->setFillColor(sf::Color(0, 75, 0, 255));
	bar->setPosition(sf::Vector2f(settings->window.width - barWidth - 17, settings->window.height - barHeight - 17));
	app->draw(*bar);


	bar->setSize(sf::Vector2f(200, 12));
	bar->setFillColor(sf::Color(0, 150, 0, 255));
	app->draw(*bar);


	if (owner->inventory->primaryAmmo.base) snprintf(outStr, sizeof(outStr), "%u", owner->inventory->primaryAmmo.count);
	else                                    snprintf(outStr, sizeof(outStr), "inf");

	*str = std::string(outStr);
	txt->setString(*str);
	txt->setPosition(sf::Vector2f(settings->window.width - barWidth - 17 + (barWidth - txt->getGlobalBounds().width) / 2.0f, settings->window.height - barHeight - 19));
	app->draw(*txt);


	// Cooldown bar
	bar->setSize(sf::Vector2f(200, 12));
	bar->setFillColor(sf::Color(75, 30, 0, 255));
	bar->setPosition(sf::Vector2f(settings->window.width - barWidth - 17, settings->window.height - barHeight - 2));
	app->draw(*bar);


	if (owner->weaponCooldown > 0) percent = (float)(owner->weapon->cooldown - owner->weaponCooldown) / (float)owner->weapon->cooldown;
	else                           percent = 1.0f;

	bar->setSize(sf::Vector2f(200 * percent, 12));
	bar->setFillColor(sf::Color(150, 60, 0, 255));
	app->draw(*bar);


	if (owner->weaponCooldown > 0) snprintf(outStr, sizeof(outStr), "%3.2f", owner->weaponCooldown);
	else                           outStr[0] = 0;

	*str = std::string(outStr);
	txt->setString(*str);
	txt->setPosition(sf::Vector2f(settings->window.width - barWidth - 17 + (barWidth - txt->getGlobalBounds().width) / 2.0f, settings->window.height - barHeight - 4));
	app->draw(*txt);
}
