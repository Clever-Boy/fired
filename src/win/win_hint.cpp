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

	win->text->setCharacterSize(12);
}



/***********************************************************************
     * HintWindow
     * destructor

***********************************************************************/
fired::HintWindow::~HintWindow() {
	delete win;
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
     * render

***********************************************************************/
void fired::HintWindow::render(fired::BaseItem *item) {
	if (item == NULL) return;
	char str[128];


	if (item->type == itAny) {
		win->setSize(sf::Vector2f(200, 40));
		win->render();

		win->renderText(5, 5, "Misc", taLeft);
	} else if (item->type == itWeapon) {
		fired::BaseWeapon *base = container->weapons[item->UID];

		if (base->type == WEAPON_TYPE_RANGED) win->setSize(sf::Vector2f(200, 145));
		else                                  win->setSize(sf::Vector2f(200, 115));
		win->render();

		win->renderText(5, 5, base->caption, taLeft);
		win->renderText(5, 20, "Weapon class:", taLeft);
		win->renderText(5, 35, "Weapon subclass:", taLeft);

		switch (base->type) {
			case WEAPON_TYPE_RANGED: win->renderText(195, 20, "ranged", taRight); break;
			case WEAPON_TYPE_MELEE : win->renderText(195, 20, "melee", taRight); break;
			case WEAPON_TYPE_BROAD : win->renderText(195, 20, "broad", taRight); break;
		}

		switch (base->subtype) {
			case WEAPON_SUBTYPE_MELEE     : win->renderText(195, 35, "melee"    , taRight); break;
			case WEAPON_SUBTYPE_BROAD     : win->renderText(195, 35, "broad"    , taRight); break;
			case WEAPON_SUBTYPE_PISTOL    : win->renderText(195, 35, "pistol"   , taRight); break;
			case WEAPON_SUBTYPE_SHOTGUN   : win->renderText(195, 35, "shotgun"  , taRight); break;
			case WEAPON_SUBTYPE_RIFLE     : win->renderText(195, 35, "rifle"    , taRight); break;
			case WEAPON_SUBTYPE_ENERGY    : win->renderText(195, 35, "energy"   , taRight); break;
			case WEAPON_SUBTYPE_EXPLOSIVE : win->renderText(195, 35, "explosive", taRight); break;
		}

		if (base->automatic) win->renderText(5, 50, "Automatic", taLeft);
		else                 win->renderText(5, 50, "Non-automatic", taLeft);

		snprintf(str, sizeof(str), "%d", base->damage);
		win->renderText(5, 65, "Damage", taLeft);
		win->renderText(195, 65, str, taRight);

		snprintf(str, sizeof(str), "%3.2f", base->knockback);
		win->renderText(5, 80, "Knockback", taLeft);
		win->renderText(195, 80, str, taRight);

		snprintf(str, sizeof(str), "%3.2f", base->range);
		win->renderText(5, 95, "Range", taLeft);
		win->renderText(195, 95, str, taRight);

		snprintf(str, sizeof(str), "%3.2f", base->cooldown);
		win->renderText(5, 110, "Cooldown", taLeft);
		win->renderText(195, 110, str, taRight);

		if (base->type == WEAPON_TYPE_RANGED) {
			snprintf(str, sizeof(str), "%3.2f", base->speed);
			win->renderText(5, 125, "Speed", taLeft);
			win->renderText(195, 125, str, taRight);
		}
	} else if (item->type == itArmor) {
		fired::BaseArmor *base = container->armors[item->UID];

		win->setSize(sf::Vector2f(200, 55));
		win->render();

		win->renderText(5, 5, base->caption, taLeft);
		win->renderText(5, 20, "Armor class:", taLeft);

		switch (base->type) {
			case acHelm: win->renderText(195, 20, "helm" , taRight); break;
			case acFist: win->renderText(195, 20, "fist" , taRight); break;
			case acBody: win->renderText(195, 20, "torso", taRight); break;
			case acLegs: win->renderText(195, 20, "legs" , taRight); break;
			case acShoe: win->renderText(195, 20, "shoes", taRight); break;
			case acArms: win->renderText(195, 20, "arms" , taRight); break;
			case acNull: break;
		}

		snprintf(str, sizeof(str), "%d", base->armor);
		win->renderText(5, 35, "Armor:", taLeft);
		win->renderText(195, 35, str, taRight);
	} else if (item->type == itAmmo) {
		fired::BaseAmmo *base = container->ammos[item->UID];

		if (base->explosive) win->setSize(sf::Vector2f(200, 70));
		else                 win->setSize(sf::Vector2f(200, 55));
		win->render();

		win->renderText(5, 5, base->caption, taLeft);
		win->renderText(5, 20, "Ammo class:", taLeft);

		switch (base->subtype) {
			case WEAPON_SUBTYPE_MELEE     : win->renderText(195, 20, "melee"    , taRight); break;
			case WEAPON_SUBTYPE_BROAD     : win->renderText(195, 20, "broad"    , taRight); break;
			case WEAPON_SUBTYPE_PISTOL    : win->renderText(195, 20, "pistol"   , taRight); break;
			case WEAPON_SUBTYPE_SHOTGUN   : win->renderText(195, 20, "shotgun"  , taRight); break;
			case WEAPON_SUBTYPE_RIFLE     : win->renderText(195, 20, "rifle"    , taRight); break;
			case WEAPON_SUBTYPE_ENERGY    : win->renderText(195, 20, "energy"   , taRight); break;
			case WEAPON_SUBTYPE_EXPLOSIVE : win->renderText(195, 20, "explosive", taRight); break;
		}

		snprintf(str, sizeof(str), "%d", base->damage);
		win->renderText(5, 35, "Damage", taLeft);
		win->renderText(195, 35, str, taRight);

		if (base->explosive) {
			snprintf(str, sizeof(str), "%3.2f", base->explosionRadius);
			win->renderText(5, 50, "Explosion radius", taLeft);
			win->renderText(195, 50, str, taRight);
		}
	}
}
