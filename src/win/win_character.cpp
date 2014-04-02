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
	win    = new fired::Window(sf::Vector2f(300, 410));

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
void fired::CharacterWindow::renderText(float x, float y, const char *caption, bool rightAligned, sf::Color color = sf::Color::White) {
	text->setColor(color);

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
	win->render();

	renderMain();
	renderSkills();
	renderStats();
}



/***********************************************************************
     * CharacterWindow
     * renderMain

***********************************************************************/
void fired::CharacterWindow::renderMain() {
	char str[128];

	snprintf(str, sizeof(str), "%d", owner->level);
	renderText( 10, 10, "Level", false);
	renderText(290, 10, str    , true);

	snprintf(str, sizeof(str), "%ld / %d", owner->HP, owner->stats.maxHP);
	renderText( 10, 30, "HP", false);
	renderText(290, 30, str , true);

	snprintf(str, sizeof(str), "%ld", owner->XP);
	renderText( 10, 50, "XP", false);
	renderText(290, 50, str , true);

	snprintf(str, sizeof(str), "%ld", owner->needXP);
	renderText( 10, 70, "Next level", false);
	renderText(290, 70, str         , true);
}



/***********************************************************************
     * CharacterWindow
     * renderSkills

***********************************************************************/
void fired::CharacterWindow::renderSkills() {
	char str[128];
	int  offset = 290;
	bool flag = (owner->attr.points > 0);

	if (flag) offset = 280;


	snprintf(str, sizeof(str), "%d", owner->attr.strength);
	renderText(10    , 110, "Strength", false);
	renderText(offset, 110, str       , true);

	snprintf(str, sizeof(str), "%d", owner->attr.dexterity);
	renderText(10    , 130, "Dexterity", false);
	renderText(offset, 130, str        , true);

	snprintf(str, sizeof(str), "%d", owner->attr.constitution);
	renderText(10   , 150, "Constitution", false);
	renderText(offset, 150, str          , true);

	snprintf(str, sizeof(str), "%d", owner->attr.intelligence);
	renderText(10    , 170, "Intelligence", false);
	renderText(offset, 170, str           , true);



	snprintf(str, sizeof(str), "%d", owner->attr.points);
	renderText( 10, 200, "Skill points", false);
	renderText(290, 200, str           , true);



	if (flag) {
		snprintf(str, sizeof(str), "+");

		renderText(290, 110, str, true, sf::Color(44, 88, 22));
		renderText(290, 130, str, true, sf::Color(44, 88, 22));
		renderText(290, 150, str, true, sf::Color(44, 88, 22));
		renderText(290, 170, str, true, sf::Color(44, 88, 22));
	}
}



/***********************************************************************
     * CharacterWindow
     * renderStats

***********************************************************************/
void fired::CharacterWindow::renderStats() {
	char str[128];

	snprintf(str, sizeof(str), "%d", owner->stats.armor);
	renderText( 10, 240, "Armor", false);
	renderText(290, 240, str    , true);

	snprintf(str, sizeof(str), "%d", owner->getDamage());
	renderText( 10, 260, "Damage", false);
	renderText(290, 260, str    , true);

	snprintf(str, sizeof(str), "%3.2f", owner->stats.speed);
	renderText( 10, 280, "Speed", false);
	renderText(290, 280, str    , true);

	snprintf(str, sizeof(str), "%3.2f", owner->stats.accel);
	renderText( 10, 300, "Acceleration", false);
	renderText(290, 300, str    , true);

	snprintf(str, sizeof(str), "%3.2f", owner->stats.aimrange);
	renderText( 10, 320, "Aim range", false);
	renderText(290, 320, str    , true);

	snprintf(str, sizeof(str), "%3.2f", owner->stats.accuracy);
	renderText( 10, 340, "Accuracy", false);
	renderText(290, 340, str    , true);

	snprintf(str, sizeof(str), "%3.2f", owner->stats.jump);
	renderText( 10, 360, "Jump", false);
	renderText(290, 360, str    , true);

	snprintf(str, sizeof(str), "%3.2f", owner->stats.xpfactor);
	renderText( 10, 380, "XP bonus", false);
	renderText(290, 380, str    , true);
}



/***********************************************************************
     * CharacterWindow
     * click

***********************************************************************/
void fired::CharacterWindow::click(sf::Vector2f mousePos) {
	if (owner->attr.points == 0) return;

	mousePos -= win->offset;
	if (mousePos.x < 280 || mousePos.x > 290) return;
	if (mousePos.y < 110 || mousePos.y > 190) return;

	     if (mousePos.y < 130) owner->attr.strength++;
	else if (mousePos.y < 150) owner->attr.dexterity++;
	else if (mousePos.y < 170) owner->attr.constitution++;
	else                       owner->attr.intelligence++;

	owner->attr.points--;
	owner->updateStats();
}
