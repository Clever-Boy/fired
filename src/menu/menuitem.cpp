#include "game.hpp"

void fired::MenuItem::init(fired::Game *_game, sf::Sprite *_sprite, sf::Font *_font, const char *_caption, fired::MenuItem *_parent, fired::MenuItemType _itemType) {
	sf::FloatRect textRect;

	game     = _game;
	font     = _font;
	sprite   = _sprite;
	parent   = _parent;
	itemType = _itemType;
	caption  = new sf::String(_caption);
	text     = new sf::Text();

	text->setFont(*font);
	text->setString(*caption);
	text->setCharacterSize(32);

	textRect = text->getGlobalBounds();
	xOffset = (sprite->getTexture()->getSize().x - textRect.width) / 2;
	return;
}


void fired::MenuItem::deinit() {
	free(caption);
	free(text);
}


void fired::MenuItem::addToParent() {
	if (parent) parent->addSubMenu(this);
}


void fired::MenuItem::addSubMenu(fired::MenuItem *subMenuItem) {
	subMenu.push_back(subMenuItem);
	subMenuItem->pos = sf::Vector2f(MENU_X_OFFSET, MENU_Y_OFFSET + MENU_Y_DIFF * subMenu.size());
}


void fired::MenuItem::update(float frameClock) {
	render();
}


void fired::MenuItem::render() {
	sprite->setPosition(pos.x, pos.y + yOffset);
	text->setPosition(pos.x + xOffset, pos.y + 1.5 + yOffset);

	game->app.draw(*sprite);
	game->app.draw(*text);
}


void fired::MenuItem::click() {
	switch (itemType) {
		case itSubmenu:
			game->mainMenu.setNextMenu(this);
			break;

		case itBack:
			if (parent->parent) game->mainMenu.setNextMenu(parent->parent);
			else game->running = false;
	}
}
