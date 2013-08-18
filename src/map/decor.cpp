#include "game.hpp"


//======================================================================


fired::BaseDecor::BaseDecor(const char *_name, const char *filename) {
	strncpy(name, _name, sizeof(name));

	tex = new sf::Texture();
	tex->loadFromFile(filename);
	tex->setSmooth(true);

	spr = new sf::Sprite();
	spr->setTexture(*tex);
}

//======================================================================


fired::BaseDecor::~BaseDecor() {
	delete tex;
	delete spr;
}

//======================================================================


fired::Decor::Decor(fired::BaseDecor *base, sf::Vector2f _pos) {
	pos    = _pos;
	sprite = base->spr;
	color  = sf::Color::White;
}

//======================================================================


void fired::Decor::render() {
	sprite->setPosition(pos);
	sprite->setColor(color);
	app->draw(*sprite);
}
