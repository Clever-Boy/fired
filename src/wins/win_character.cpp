/***********************************************************************
     * File       : win_character.cpp
     * Created    : Aug 28, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * CharacterWindow
     * constructor

***********************************************************************/
fired::CharacterWindow::CharacterWindow(fired::Character *_owner) {
	owner  = _owner;
	win    = new fired::Window(sf::Vector2f(400, 200));

	text = new sf::Text();
	text->setFont(*game->font);
	text->setCharacterSize(16);
	text->setPosition(win->offset + sf::Vector2f(30.0f, 360.0f));
	text->setColor(sf::Color::White);
}



/***********************************************************************
     * CharacterWindow
     * destructor

***********************************************************************/
fired::CharacterWindow::~CharacterWindow() {
	delete win;
	delete text;
}



/***********************************************************************
     * CharacterWindow
     * update

***********************************************************************/
void fired::CharacterWindow::update() {
	render();
}



/***********************************************************************
     * CharacterWindow
     * renderText

***********************************************************************/
void fired::CharacterWindow::renderText(float x, float y, const char *caption, bool rightAligned) {
	if (rightAligned) {
		text->setString(sf::String(caption));
		text->setPosition(win->offset + sf::Vector2f(x - text->getGlobalBounds().width, y));
		app->draw(*text);
	} else {
		text->setString(sf::String(caption));
		text->setPosition(win->offset + sf::Vector2f(x, y));
		app->draw(*text);
	}
}



/***********************************************************************
     * CharacterWindow
     * render

***********************************************************************/
void fired::CharacterWindow::render() {
	char str[128];
	win->render();

	snprintf(str, sizeof(str), "%d", owner->level);
	renderText( 10, 10, "Level", false);
	renderText(390, 10, str    , true);

	snprintf(str, sizeof(str), "%d / %d", owner->baseStats.HP, owner->baseStats.maxHP);
	renderText( 10, 30, "HP", false);
	renderText(390, 30, str , true);

	snprintf(str, sizeof(str), "%ld", owner->XP);
	renderText( 10, 50, "XP", false);
	renderText(390, 50, str , true);

	snprintf(str, sizeof(str), "%ld", owner->needXP);
	renderText( 10, 70, "Next level", false);
	renderText(390, 70, str         , true);


	snprintf(str, sizeof(str), "%d", owner->baseStats.armor);
	renderText( 10, 110, "Armor", false);
	renderText(390, 110, str    , true);

	snprintf(str, sizeof(str), "%d", owner->getDamage());
	renderText( 10, 130, "Damage", false);
	renderText(390, 130, str    , true);

	snprintf(str, sizeof(str), "%3.2f", owner->baseStats.speed);
	renderText( 10, 150, "Speed", false);
	renderText(390, 150, str    , true);

	snprintf(str, sizeof(str), "%3.2f", owner->baseStats.jump);
	renderText( 10, 170, "Jump", false);
	renderText(390, 170, str    , true);
}
