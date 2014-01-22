/***********************************************************************
     * File       : win_exchange.cpp
     * Created    : Aug 28, 2013
     * Copyright  : (C) 2013 Achpile
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

	emptyTex = new sf::Texture();
	hoverTex = new sf::Texture();
	normalTex = new sf::Texture();

	emptyTex->loadFromFile("data/img/gui/inventory/empty.tga");
	hoverTex->loadFromFile("data/img/gui/inventory/hover.tga");
	normalTex->loadFromFile("data/img/gui/inventory/normal.tga");

	emptySpr = new sf::Sprite();
	hoverSpr = new sf::Sprite();
	normalSpr = new sf::Sprite();

	emptySpr->setTexture(*emptyTex);
	hoverSpr->setTexture(*hoverTex);
	normalSpr->setTexture(*normalTex);

	emptySpr->setOrigin(sf::Vector2f(emptyTex->getSize())   / 2.0f);
	hoverSpr->setOrigin(sf::Vector2f(hoverTex->getSize())   / 2.0f);
	normalSpr->setOrigin(sf::Vector2f(normalTex->getSize()) / 2.0f);

	moneyText = new sf::Text();
	moneyText->setFont(*game->font);
	moneyText->setCharacterSize(16);
	moneyText->setPosition(winOffset + sf::Vector2f(30.0f, 360.0f));
	moneyText->setColor(sf::Color::White);

	countText = new sf::Text();
	countText->setFont(*game->font);
	countText->setCharacterSize(12);
	countText->setColor(sf::Color::White);

	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(175.0f,  10.0f), &owner->inventory->helm, itArmor));
	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(175.0f,  65.0f), &owner->inventory->body, itArmor));
	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(130.0f,  22.0f), &owner->inventory->arms, itArmor));
	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(130.0f,  85.0f), &owner->inventory->fist, itArmor));
	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(220.0f,  25.0f), &owner->inventory->legs, itArmor));
	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(220.0f,  85.0f), &owner->inventory->shoe, itArmor));

	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(155.0f, 130.0f), &owner->inventory->primaryWeapon, itWeapon));
	items.push_back(new fired::InventoryWindowItem(winOffset + sf::Vector2f(195.0f, 130.0f), &owner->inventory->secondaryWeapon, itWeapon));


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

	delete emptySpr;
	delete hoverSpr;
	delete normalSpr;

	delete emptyTex;
	delete hoverTex;
	delete normalTex;

	delete inHand->item;
	delete inHand;

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
		if      (items[i]->hover)              items[i]->render(hoverSpr, countText);
		else if (items[i]->item->base == NULL) items[i]->render(emptySpr, countText);
		else                                   items[i]->render(normalSpr, countText);

	for (unsigned int i = 0; i < exchange.size(); i++)
		if      (exchange[i]->hover)              exchange[i]->render(hoverSpr, countText);
		else if (exchange[i]->item->base == NULL) exchange[i]->render(emptySpr, countText);
		else                                      exchange[i]->render(normalSpr, countText);


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

