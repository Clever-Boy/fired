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

	win->text->setCharacterSize(16);
}



/***********************************************************************
     * CharacterWindow
     * destructor

***********************************************************************/
fired::CharacterWindow::~CharacterWindow() {
	delete win;
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
	win->renderText( 10, 10, "Level", taLeft);
	win->renderText(290, 10, str    , taRight);

	snprintf(str, sizeof(str), "%ld / %d", owner->HP, owner->stats.maxHP);
	win->renderText( 10, 30, "HP", taLeft);
	win->renderText(290, 30, str , taRight);

	snprintf(str, sizeof(str), "%ld", owner->XP);
	win->renderText( 10, 50, "XP", taLeft);
	win->renderText(290, 50, str , taRight);

	snprintf(str, sizeof(str), "%ld", owner->needXP);
	win->renderText( 10, 70, "Next level", taLeft);
	win->renderText(290, 70, str         , taRight);
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
	win->renderText(10    , 110, "Strength", taLeft);
	win->renderText(offset, 110, str       , taRight);

	snprintf(str, sizeof(str), "%d", owner->attr.dexterity);
	win->renderText(10    , 130, "Dexterity", taLeft);
	win->renderText(offset, 130, str        , taRight);

	snprintf(str, sizeof(str), "%d", owner->attr.constitution);
	win->renderText(10   , 150, "Constitution", taLeft);
	win->renderText(offset, 150, str          , taRight);

	snprintf(str, sizeof(str), "%d", owner->attr.intelligence);
	win->renderText(10    , 170, "Intelligence", taLeft);
	win->renderText(offset, 170, str           , taRight);



	snprintf(str, sizeof(str), "%d", owner->attr.points);
	win->renderText( 10, 200, "Skill points", taLeft);
	win->renderText(290, 200, str           , taRight);



	if (flag) {
		snprintf(str, sizeof(str), "+");

		win->renderText(290, 110, str, taRight, sf::Color(44, 88, 22));
		win->renderText(290, 130, str, taRight, sf::Color(44, 88, 22));
		win->renderText(290, 150, str, taRight, sf::Color(44, 88, 22));
		win->renderText(290, 170, str, taRight, sf::Color(44, 88, 22));
	}
}



/***********************************************************************
     * CharacterWindow
     * renderStats

***********************************************************************/
void fired::CharacterWindow::renderStats() {
	char str[128];

	snprintf(str, sizeof(str), "%d", owner->stats.armor);
	win->renderText( 10, 240, "Armor", taLeft);
	win->renderText(290, 240, str    , taRight);

	snprintf(str, sizeof(str), "%d", owner->getDamage());
	win->renderText( 10, 260, "Damage", taLeft);
	win->renderText(290, 260, str    , taRight);

	snprintf(str, sizeof(str), "%3.2f", owner->stats.speed);
	win->renderText( 10, 280, "Speed", taLeft);
	win->renderText(290, 280, str    , taRight);

	snprintf(str, sizeof(str), "%3.2f", owner->stats.accel);
	win->renderText( 10, 300, "Acceleration", taLeft);
	win->renderText(290, 300, str    , taRight);

	snprintf(str, sizeof(str), "%3.2f", owner->stats.aimrange);
	win->renderText( 10, 320, "Aim range", taLeft);
	win->renderText(290, 320, str    , taRight);

	snprintf(str, sizeof(str), "%3.2f", owner->stats.accuracy);
	win->renderText( 10, 340, "Accuracy", taLeft);
	win->renderText(290, 340, str    , taRight);

	snprintf(str, sizeof(str), "%3.2f", owner->stats.jump);
	win->renderText( 10, 360, "Jump", taLeft);
	win->renderText(290, 360, str    , taRight);

	snprintf(str, sizeof(str), "%3.2f", owner->stats.xpfactor);
	win->renderText( 10, 380, "XP bonus", taLeft);
	win->renderText(290, 380, str    , taRight);
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
