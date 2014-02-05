/***********************************************************************
     * File       : win_exchange.cpp
     * Created    : Aug 28, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * ExchangeWindow
     * constructor

***********************************************************************/
fired::ExchangeWindow::ExchangeWindow(fired::Character *_owner, fired::World *world) {
	owner  = _owner;
	win    = new fired::Window(sf::Vector2f(740, 380));
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

	trashCan = new fired::InventoryWindowItem(winOffset + sf::Vector2f(325.0f, 130.0f), &owner->inventory->trash, itAny);

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(10.0f + 35.0f * i, 185.0f + 35.0f * j), &owner->inventory->items[i][j], itAny));
}



/***********************************************************************
     * ExchangeWindow
     * destructor

***********************************************************************/
fired::ExchangeWindow::~ExchangeWindow() {
	delete win;
	delete hint;
	delete moneyText;
	delete countText;

	delete inHand->item;
	delete inHand;
	delete trashCan;

	deleteList(items);
	deleteList(exchange);
}



/***********************************************************************
     * ExchangeWindow
     * init

***********************************************************************/
void fired::ExchangeWindow::init(fired::MapObjectCollector *collector) {
	deleteList(exchange);
	sf::Vector2f winOffset = win->offset;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			exchange.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(380.0f + 35.0f * i, 185.0f + 35.0f * j), &collector->items[i][j], itAny));
}



/***********************************************************************
     * ExchangeWindow
     * update

***********************************************************************/
void fired::ExchangeWindow::update(sf::Vector2f mousePos) {
	for (unsigned int i = 0; i < items.size(); i++)
		if (items[i]->rect.contains(mousePos)) items[i]->hover = true;
		else                                   items[i]->hover = false;

	for (unsigned int i = 0; i < exchange.size(); i++)
		if (exchange[i]->rect.contains(mousePos)) exchange[i]->hover = true;
		else                                      exchange[i]->hover = false;

	if (trashCan->rect.contains(mousePos)) trashCan->hover = true;
	else                                   trashCan->hover = false;

	hint->win->setOffset(mousePos + sf::Vector2f(16.0f, 16.0f));
	inHand->rect.left = mousePos.x + 16.0f;
	inHand->rect.top  = mousePos.y + 16.0f;

	render();
}



/***********************************************************************
     * ExchangeWindow
     * render

***********************************************************************/
void fired::ExchangeWindow::render() {
	win->render();

	for (unsigned int i = 0; i < items.size(); i++)
		if      (items[i]->hover)              items[i]->render(resources->win.hoverSpr , countText);
		else if (items[i]->item->base == NULL) items[i]->render(resources->win.emptySpr , countText);
		else                                   items[i]->render(resources->win.normalSpr, countText);

	for (unsigned int i = 0; i < exchange.size(); i++)
		if      (exchange[i]->hover)              exchange[i]->render(resources->win.hoverSpr , countText);
		else if (exchange[i]->item->base == NULL) exchange[i]->render(resources->win.emptySpr , countText);
		else                                      exchange[i]->render(resources->win.normalSpr, countText);

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
	else {
		for (unsigned int i = 0; i < items.size(); i++)
			if (items[i]->hover && items[i]->item->base != NULL) {
				hint->update(items[i]->item->base);
				break;
			}

		for (unsigned int i = 0; i < exchange.size(); i++)
			if (exchange[i]->hover && exchange[i]->item->base != NULL) {
				hint->update(exchange[i]->item->base);
				break;
			}
	}
}



/***********************************************************************
     * ExchangeWindow
     * click

***********************************************************************/
void fired::ExchangeWindow::click(sf::Vector2f mousePos) {
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

	for (unsigned int i = 0; i < exchange.size(); i++)
		if (exchange[i]->rect.contains(mousePos)) {
			selected = exchange[i];
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
     * ExchangeWindow
     * clickRight

***********************************************************************/
void fired::ExchangeWindow::clickRight(sf::Vector2f mousePos) {
	fired::InventoryWindowItem *selected = NULL;

	for (unsigned int i = 0; i < items.size(); i++)
		if (items[i]->rect.contains(mousePos)) {
			selected = items[i];
			break;
		}

	for (unsigned int i = 0; i < exchange.size(); i++)
		if (exchange[i]->rect.contains(mousePos)) {
			selected = exchange[i];
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
