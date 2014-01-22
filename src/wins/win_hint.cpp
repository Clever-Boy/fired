/***********************************************************************
     * File       : win_hint.cpp
     * Created    : Sep 01, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * HintWindow
     * constructor

***********************************************************************/
fired::HintWindow::HintWindow(fired::World *_world) {
	win   = new fired::Window(sf::Vector2f(150, 50));
	world = _world;

	text = new sf::Text();
	text->setFont(*game->font);
	text->setCharacterSize(12);
	text->setPosition(win->offset + sf::Vector2f(30.0f, 360.0f));
	text->setColor(sf::Color::White);
}



/***********************************************************************
     * HintWindow
     * destructor

***********************************************************************/
fired::HintWindow::~HintWindow() {
	delete win;
	delete text;
}



/***********************************************************************
     * HintWindow
     * update

***********************************************************************/
void fired::HintWindow::update(fired::BaseItem *_item) {
	render(_item);
}



/***********************************************************************
     * HintWindow
     * renderText

***********************************************************************/
void fired::HintWindow::renderText(float x, float y, const char *caption, bool rightAligned) {
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
     * HintWindow
     * render

***********************************************************************/
void fired::HintWindow::render(fired::BaseItem *item) {
	if (item == NULL) return;
	char str[128];


	if (item->type == itAny) {
		win->setSize(sf::Vector2f(150, 40));
		win->render();

		renderText(5, 5, "Misc", false);
	} else if (item->type == itWeapon) {
		fired::BaseWeapon *base = container->weapons[item->UID];

		if (base->type == WEAPON_TYPE_RANGED) win->setSize(sf::Vector2f(150, 145));
		else                                  win->setSize(sf::Vector2f(150, 115));
		win->render();

		renderText(5, 5, base->caption, false);
		renderText(5, 20, "Weapon class:", false);

		switch (base->type) {
			case WEAPON_TYPE_RANGED: renderText(145, 20, "ranged", true); break;
			case WEAPON_TYPE_MELEE : renderText(145, 20, "melee", true); break;
			case WEAPON_TYPE_BROAD : renderText(145, 20, "broad", true); break;
		}

		if (base->automatic) renderText(5, 35, "Automatic", false);
		else                 renderText(5, 35, "Non-automatic", false);

		renderText(5, 50, "Damage", false);
		snprintf(str, sizeof(str), "%d", base->damage);
		renderText(145, 50, str, true);

		renderText(5, 65, "Knockback", false);
		snprintf(str, sizeof(str), "%3.2f", base->knockback);
		renderText(145, 65, str, true);

		renderText(5, 80, "Range", false);
		snprintf(str, sizeof(str), "%3.2f", base->range);
		renderText(145, 80, str, true);

		renderText(5, 95, "Cooldown", false);
		snprintf(str, sizeof(str), "%3.2f", base->cooldown);
		renderText(145, 95, str, true);

		if (base->type == WEAPON_TYPE_RANGED) {
			renderText(5, 125, "Speed", false);
			snprintf(str, sizeof(str), "%3.2f", base->speed);
			renderText(145, 125, str, true);
		}
	} else {
		fired::BaseArmor *base = container->armors[item->UID];

		win->setSize(sf::Vector2f(150, 55));
		win->render();

		renderText(5, 5, base->caption, false);
		renderText(5, 20, "Armor class:", false);

		switch (base->type) {
			case acHelm: renderText(145, 20, "helm" , true); break;
			case acFist: renderText(145, 20, "fist" , true); break;
			case acBody: renderText(145, 20, "torso", true); break;
			case acLegs: renderText(145, 20, "legs" , true); break;
			case acShoe: renderText(145, 20, "shoes", true); break;
			case acArms: renderText(145, 20, "arms" , true); break;
		}

		renderText(5, 35, "Armor:", false);
		snprintf(str, sizeof(str), "%d", base->armor);
		renderText(145, 35, str, true);
	}
}
