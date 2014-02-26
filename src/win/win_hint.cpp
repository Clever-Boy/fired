/***********************************************************************
     * File       : win_hint.cpp
     * Created    : Sep 01, 2013
     * Copyright  : (C) 2014 Achpile
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
		win->setSize(sf::Vector2f(200, 40));
		win->render();

		renderText(5, 5, "Misc", false);
	} else if (item->type == itWeapon) {
		fired::BaseWeapon *base = container->weapons[item->UID];

		if (base->explosive)                       win->setSize(sf::Vector2f(200, 160));
		else if (base->type == WEAPON_TYPE_RANGED) win->setSize(sf::Vector2f(200, 145));
		else                                       win->setSize(sf::Vector2f(200, 115));
		win->render();

		renderText(5, 5, base->caption, false);
		renderText(5, 20, "Weapon class:", false);
		renderText(5, 35, "Weapon subclass:", false);

		switch (base->type) {
			case WEAPON_TYPE_RANGED: renderText(195, 20, "ranged", true); break;
			case WEAPON_TYPE_MELEE : renderText(195, 20, "melee", true); break;
			case WEAPON_TYPE_BROAD : renderText(195, 20, "broad", true); break;
		}

		switch (base->subtype) {
			case WEAPON_SUBTYPE_MELEE     : renderText(195, 35, "melee"    , true); break;
			case WEAPON_SUBTYPE_BROAD     : renderText(195, 35, "broad"    , true); break;
			case WEAPON_SUBTYPE_PISTOL    : renderText(195, 35, "pistol"   , true); break;
			case WEAPON_SUBTYPE_SHOTGUN   : renderText(195, 35, "shotgun"  , true); break;
			case WEAPON_SUBTYPE_RIFLE     : renderText(195, 35, "rifle"    , true); break;
			case WEAPON_SUBTYPE_ENERGY    : renderText(195, 35, "energy"   , true); break;
			case WEAPON_SUBTYPE_EXPLOSIVE : renderText(195, 35, "explosive", true); break;
		}

		if (base->automatic) renderText(5, 50, "Automatic", false);
		else                 renderText(5, 50, "Non-automatic", false);

		renderText(5, 65, "Damage", false);
		snprintf(str, sizeof(str), "%d", base->damage);
		renderText(195, 65, str, true);

		renderText(5, 80, "Knockback", false);
		snprintf(str, sizeof(str), "%3.2f", base->knockback);
		renderText(195, 80, str, true);

		renderText(5, 95, "Range", false);
		snprintf(str, sizeof(str), "%3.2f", base->range);
		renderText(195, 95, str, true);

		renderText(5, 110, "Cooldown", false);
		snprintf(str, sizeof(str), "%3.2f", base->cooldown);
		renderText(195, 110, str, true);

		if (base->type == WEAPON_TYPE_RANGED) {
			renderText(5, 125, "Speed", false);
			snprintf(str, sizeof(str), "%3.2f", base->speed);
			renderText(195, 125, str, true);
		}

		if (base->explosive) {
			renderText(5, 140, "Explosion radius", false);
			snprintf(str, sizeof(str), "%3.2f", base->explosionRadius);
			renderText(195, 140, str, true);
		}
	} else if (item->type == itArmor) {
		fired::BaseArmor *base = container->armors[item->UID];

		win->setSize(sf::Vector2f(200, 55));
		win->render();

		renderText(5, 5, base->caption, false);
		renderText(5, 20, "Armor class:", false);

		switch (base->type) {
			case acHelm: renderText(195, 20, "helm" , true); break;
			case acFist: renderText(195, 20, "fist" , true); break;
			case acBody: renderText(195, 20, "torso", true); break;
			case acLegs: renderText(195, 20, "legs" , true); break;
			case acShoe: renderText(195, 20, "shoes", true); break;
			case acArms: renderText(195, 20, "arms" , true); break;
			case acNull: break;
		}

		renderText(5, 35, "Armor:", false);
		snprintf(str, sizeof(str), "%d", base->armor);
		renderText(195, 35, str, true);
	} else if (item->type == itAmmo) {
		fired::BaseAmmo *base = container->ammos[item->UID];

		if (base->explosive) win->setSize(sf::Vector2f(200, 70));
		else                 win->setSize(sf::Vector2f(200, 55));
		win->render();

		renderText(5, 5, base->caption, false);
		renderText(5, 20, "Ammo class:", false);

		switch (base->subtype) {
			case WEAPON_SUBTYPE_MELEE     : renderText(195, 20, "melee"    , true); break;
			case WEAPON_SUBTYPE_BROAD     : renderText(195, 20, "broad"    , true); break;
			case WEAPON_SUBTYPE_PISTOL    : renderText(195, 20, "pistol"   , true); break;
			case WEAPON_SUBTYPE_SHOTGUN   : renderText(195, 20, "shotgun"  , true); break;
			case WEAPON_SUBTYPE_RIFLE     : renderText(195, 20, "rifle"    , true); break;
			case WEAPON_SUBTYPE_ENERGY    : renderText(195, 20, "energy"   , true); break;
			case WEAPON_SUBTYPE_EXPLOSIVE : renderText(195, 20, "explosive", true); break;
		}

		renderText(5, 35, "Damage", false);
		snprintf(str, sizeof(str), "%d", base->damage);
		renderText(195, 35, str, true);

		if (base->explosive) {
			renderText(5, 50, "Explosion radius", false);
			snprintf(str, sizeof(str), "%3.2f", base->explosionRadius);
			renderText(195, 50, str, true);
		}
	}
}
