#include "game.hpp"

//======================================================================


fired::GameSprite::GameSprite(const char *filename) {
	tex = new sf::Texture();
	tex->loadFromFile(filename);
	tex->setSmooth(true);

	spr = new sf::Sprite();
	spr->setTexture(*tex);

	size = sf::Vector2f(tex->getSize());
}

//======================================================================


fired::GameSprite::~GameSprite() {
	delete spr;
	delete tex;
}
