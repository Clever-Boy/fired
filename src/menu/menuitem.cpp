#include "game.hpp"


void fired::MenuItem::init(fired::Game *_game, fired::MainMenu *_mainMenu, sf::Sprite *_sprite, const char *_caption, fired::MenuItem *_parent, fired::MenuItemType _itemType, fired::Handler _handlerFunc) {
	sf::FloatRect textRect;

	game        = _game;
	app         = game->getApp();
	font        = game->getFont();
	mainMenu    = _mainMenu;
	sprite      = _sprite;
	parent      = _parent;
	itemType    = _itemType;
	handlerFunc = _handlerFunc;
	caption     = new sf::String(_caption);
	text        = new sf::Text();

	text->setFont(*font);
	text->setString(*caption);
	text->setCharacterSize(32);

	textRect = text->getGlobalBounds();
	xOffset = (sprite->getTexture()->getSize().x - textRect.width) / 2;
}



void fired::MenuItem::deinit() {
	delete caption;
	delete text;
}



void fired::MenuItem::addToParent() {
	if (parent) parent->addSubMenu(this);
}



void fired::MenuItem::addSubMenu(fired::MenuItem *subMenuItem) {
	subMenu.push_back(subMenuItem);
	subMenuItem->pos = sf::Vector2f(MENU_X_OFFSET, MENU_Y_OFFSET + MENU_Y_DIFF * subMenu.size());
}



void fired::MenuItem::update() {
	render();
}



void fired::MenuItem::render() {
	sprite->setPosition(pos.x, pos.y + yOffset);
	text->setPosition(pos.x + xOffset, pos.y + 1.5 + yOffset);

	app->draw(*sprite);
	app->draw(*text);
}



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
