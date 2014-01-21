#include "game.hpp"


//======================================================================


fired::MapDecor::MapDecor(const char *_name, sf::Vector2f _pos) {
	strncpy(name, _name, sizeof(name));
	pos = _pos;
}

//======================================================================


fired::BaseDecor::BaseDecor(const char *_name, sf::Vector2f _size, fired::GameSprite *_sprite) {
	strncpy(name, _name, sizeof(name));

	size = _size;
	sprite = _sprite;
}

//======================================================================


fired::Decor::Decor(fired::BaseDecor *base, sf::Vector2f _pos) {
	pos    = _pos;
	rect   = sf::FloatRect(pos, base->size);
	sprite = base->sprite->spr;
	color  = sf::Color::White;
}

//======================================================================


void fired::Decor::render() {
	sprite->setPosition(pos);
	sprite->setColor(color);
	app->draw(*sprite);
}
