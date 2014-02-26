/***********************************************************************
     * File       : win_inventory.cpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * InventoryWindow
     * constructor

***********************************************************************/
fired::InventoryWindow::InventoryWindow(fired::Character *_owner, fired::World *world) {
	owner  = _owner;
	win    = new fired::Window(sf::Vector2f(370, 380));
	hint   = new fired::HintWindow(world);
	inHand = new fired::InventoryWindowItem(sf::Vector2f(0.0f, 0.0f), new fired::InventoryItem, itAny);

	sf::Vector2f winOffset = win->offset;

	moneyText = new sf::Text();
	moneyText->setFont(*game->font);
	moneyText->setCharacterSize(16);
	moneyText->setPosition(winOffset + sf::Vector2f(30.0f, 360.0f));
	moneyText->setColor(sf::Color::White);

	countText = new sf::Text();
	countText->setFont(*game->font);
	countText->setCharacterSize(12);
	countText->setColor(sf::Color::White);

	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(175.0f,  10.0f), &owner->inventory->helm, itArmor, acHelm));
	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(175.0f,  65.0f), &owner->inventory->body, itArmor, acBody));
	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(130.0f,  22.0f), &owner->inventory->arms, itArmor, acArms));
	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(130.0f,  85.0f), &owner->inventory->fist, itArmor, acFist));
	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(220.0f,  25.0f), &owner->inventory->legs, itArmor, acLegs));
	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(220.0f,  85.0f), &owner->inventory->shoe, itArmor, acShoe));

	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(155.0f, 130.0f), &owner->inventory->primaryWeapon, itWeapon));
	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(195.0f, 130.0f), &owner->inventory->secondaryWeapon, itWeapon));

	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(120.0f, 130.0f), &owner->inventory->primaryAmmo, itAmmo));
	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(230.0f, 130.0f), &owner->inventory->secondaryAmmo, itAmmo));

	trashCan = new fired::InventoryWindowItem(winOffset + sf::Vector2f(325.0f, 130.0f), &owner->inventory->trash, itAny);


	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(10.0f + 35.0f * i, 185.0f + 35.0f * j), &owner->inventory->items[i][j], itAny));
}



/***********************************************************************
     * InventoryWindow
     * destructor

***********************************************************************/
fired::InventoryWindow::~InventoryWindow() {
	delete win;
	delete hint;
	delete moneyText;
	delete countText;

	delete inHand->item;
	delete inHand;
	delete trashCan;

	deleteList(items);
}



/***********************************************************************
     * InventoryWindow
     * update

***********************************************************************/
void fired::InventoryWindow::update(sf::Vector2f mousePos) {
	for (unsigned int i = 0; i < items.size(); i++)
		if (items[i]->rect.contains(mousePos)) items[i]->hover = true;
		else                                   items[i]->hover = false;

	if (trashCan->rect.contains(mousePos)) trashCan->hover = true;
	else                                   trashCan->hover = false;

	hint->win->setOffset(mousePos + sf::Vector2f(16.0f, 16.0f));
	inHand->rect.left = mousePos.x + 16.0f;
	inHand->rect.top  = mousePos.y + 16.0f;

	render();
}



/***********************************************************************
     * InventoryWindow
     * render

***********************************************************************/
void fired::InventoryWindow::render() {
	win->render();

	for (unsigned int i = 0; i < items.size(); i++)
		if      (items[i]->hover)              items[i]->render(resources->win.hoverSpr , countText);
		else if (items[i]->item->base == NULL) items[i]->render(resources->win.emptySpr , countText);
		else                                   items[i]->render(resources->win.normalSpr, countText);

	if (trashCan->item->base == NULL) trashCan->render(resources->win.trashSpr , countText);
	else if (trashCan->hover)         trashCan->render(resources->win.hoverSpr , countText);
	else                              trashCan->render(resources->win.normalSpr, countText);


	resources->sprites.coin->setPosition(win->offset + sf::Vector2f(20.0f, 370.0f));
	app->draw(*resources->sprites.coin);

	char credits[16];
	snprintf(credits, sizeof(credits), "%u", owner->inventory->credits);
	moneyText->setString(sf::String(credits));
	app->draw(*moneyText);

	if (inHand->item->base) inHand->renderItem(countText);
	else
		for (unsigned int i = 0; i < items.size(); i++)
			if (items[i]->hover && items[i]->item->base != NULL) {
				hint->update(items[i]->item->base);
				break;
			}
}



/***********************************************************************
     * InventoryWindow
     * click

***********************************************************************/
void fired::InventoryWindow::click(sf::Vector2f mousePos) {
	fired::InventoryWindowItem *selected = NULL;

	if (trashCan->rect.contains(mousePos)) {
		if (inHand->item->base != NULL) emptyItem(trashCan->item);
		swapItems(trashCan->item, inHand->item);
		return;
	}


	for (unsigned int i = 0; i < items.size(); i++)
		if (items[i]->rect.contains(mousePos)) {
			selected = items[i];
			break;
		}

	if (selected == NULL) return;

	if (inHand->item->base != NULL) {
		if (selected->filter != itAny && selected->filter != inHand->item->base->type) return;
		if (selected->filter == itArmor && selected->armorFilter != container->armors[inHand->item->base->UID]->type) return;

		if (selected->item->base == inHand->item->base) {
			if (selected->item->count + inHand->item->count <= selected->item->base->maxStack) {
				selected->item->count += inHand->item->count;
				emptyItem(inHand->item);
			} else {
				inHand->item->count = selected->item->count + inHand->item->count - selected->item->base->maxStack;
				selected->item->count = selected->item->base->maxStack;
			}

			owner->updateEquip();
			return;
		}
	}

	swapItems(selected->item, inHand->item);
	owner->updateEquip();
}



/***********************************************************************
     * InventoryWindow
     * clickRight

***********************************************************************/
void fired::InventoryWindow::clickRight(sf::Vector2f mousePos) {
	fired::InventoryWindowItem *selected = NULL;

	for (unsigned int i = 0; i < items.size(); i++)
		if (items[i]->rect.contains(mousePos)) {
			selected = items[i];
			break;
		}

	if (selected == NULL) return;
	if (selected->item->base == NULL) return;
	if (selected->item->count == 0) return;

	if ((inHand->item->base == NULL) || ((selected->item->base == inHand->item->base) && (inHand->item->count != inHand->item->base->maxStack))) {
		if (inHand->item->base == NULL) inHand->item->base = selected->item->base;

		inHand->item->count++;
		selected->item->count--;
		if (selected->item->count == 0) emptyItem(selected->item);

		owner->updateEquip();
	}
}
