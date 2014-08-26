/***********************************************************************
     * File       : menu_item.cpp
     * Created    : Jul 18, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MenuItem
     * constructor

***********************************************************************/
fired::MenuItem::MenuItem(fired::MainMenu *_mainMenu, sf::Sprite *_sprite, const char *_caption, fired::MenuItem *_parent, fired::MenuItemType _itemType, fired::Handler _handlerFunc, fired::MenuItemWindow *_window) {
	sf::FloatRect textRect;

	font        = resources->fonts.menu;
	mainMenu    = _mainMenu;
	sprite      = _sprite;
	parent      = _parent;
	window      = _window;
	itemType    = _itemType;
	handlerFunc = _handlerFunc;
	caption     = new sf::String(_caption);
	text        = new sf::Text();

	text->setFont(*font);
	text->setString(*caption);
	text->setCharacterSize(24);

	textRect = text->getGlobalBounds();
	xOffset = (sprite->getTexture()->getSize().x - textRect.width) / 2;
}



/***********************************************************************
     * MenuItem
     * destructor

***********************************************************************/
fired::MenuItem::~MenuItem() {
	if (window) delete window;

	delete caption;
	delete text;
}



/***********************************************************************
     * MenuItem
     * addToParent

***********************************************************************/
void fired::MenuItem::addToParent() {
	if (parent) parent->addSubMenu(this);
}



/***********************************************************************
     * MenuItem
     * addSubMenu

***********************************************************************/
void fired::MenuItem::addSubMenu(fired::MenuItem *subMenuItem) {
	subMenu.push_back(subMenuItem);
	subMenuItem->pos = sf::Vector2f(MENU_X_OFFSET, MENU_Y_OFFSET + MENU_Y_DIFF * subMenu.size());
}



/***********************************************************************
     * MenuItem
     * update

***********************************************************************/
void fired::MenuItem::update() {
	render();
	if (window) window->update();
}



/***********************************************************************
     * MenuItem
     * render

***********************************************************************/
void fired::MenuItem::render() {
	sprite->setPosition(pos.x, pos.y + yOffset);
	text->setPosition(pos.x + xOffset, pos.y + 8.5 + yOffset);

	app->draw(*sprite);
	app->draw(*text);
}



/***********************************************************************
     * MenuItem
     * click

***********************************************************************/
void fired::MenuItem::click() {
	switch (itemType) {
		case itSubmenu:
			mainMenu->setNextMenu(this);
			break;

		case itBack:
			mainMenu->setNextMenu(parent->parent);
			break;

		case itButton:
			game->processHandler(handlerFunc);
			break;
	}
}
