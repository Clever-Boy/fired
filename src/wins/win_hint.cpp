#include "game.hpp"

//======================================================================


fired::HintWindow::HintWindow(fired::World *_world) {
	win   = new fired::Window(sf::Vector2f(150, 50));
	world = _world;

	text = new sf::Text();
	text->setFont(*game->getFont());
	text->setCharacterSize(12);
	text->setPosition(win->getOffset() + sf::Vector2f(30.0f, 360.0f));
	text->setColor(sf::Color::White);
}

//======================================================================


fired::HintWindow::~HintWindow() {
	delete win;
	delete text;
}

//======================================================================


void fired::HintWindow::update(fired::InventoryItem *item) {
	render(item);
}

//======================================================================


void fired::HintWindow::renderText(float x, float y, const char *caption, bool rightAligned) {
	if (rightAligned) {
		text->setString(sf::String(caption));
		text->setPosition(win->getOffset() + sf::Vector2f(x - text->getGlobalBounds().width, y));
		app->draw(*text);
	} else {
		text->setString(sf::String(caption));
		text->setPosition(win->getOffset() + sf::Vector2f(x, y));
		app->draw(*text);
	}
}

//======================================================================


void fired::HintWindow::render(fired::InventoryItem *item) {
	if (item == NULL) return;
	char str[128];


	if (item->type == itMoney) {
		win->setSize(sf::Vector2f(150, 40));
		win->render();

		renderText(5, 5, "Credits", false);
		renderText(5, 20, "Count:", false);

		snprintf(str, sizeof(str), "%d", item->count);
		renderText(145, 20, str, true);
	} else if (item->type == itAny) {
		win->setSize(sf::Vector2f(150, 40));
		win->render();

		renderText(5, 5, "Misc", false);
		renderText(5, 20, "Count:", false);

		snprintf(str, sizeof(str), "%d", item->count);
		renderText(145, 20, str, true);
	} else if (item->type == itWeapon) {
		fired::BaseWeapon *base = world->getWeapon(item->name);

		if (base->type == WEAPON_TYPE_RANGED) win->setSize(sf::Vector2f(150, 145));
		else                                  win->setSize(sf::Vector2f(150, 115));
		win->render();

		renderText(5, 5, base->name, false);
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
			renderText(5, 110, "Reload", false);
			snprintf(str, sizeof(str), "%3.2f", base->reload);
			renderText(145, 110, str, true);

			renderText(5, 125, "Speed", false);
			snprintf(str, sizeof(str), "%3.2f", base->speed);
			renderText(145, 125, str, true);
		}
	} else {
		fired::BaseArmor *base;

		switch (item->type) {
			case itArmorHelm: base = world->getArmor(item->name, acHelm); break;
			case itArmorFist: base = world->getArmor(item->name, acFist); break;
			case itArmorBody: base = world->getArmor(item->name, acBody); break;
			case itArmorLegs: base = world->getArmor(item->name, acLegs); break;
			case itArmorShoe: base = world->getArmor(item->name, acShoe); break;
			case itArmorArms: base = world->getArmor(item->name, acArms); break;

			case itMoney:
			case itWeapon:
			case itAny:
				return;
		}

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
