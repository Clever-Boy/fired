#include "game.hpp"

//======================================================================


fired::GameSprite::GameSprite(const char *_name, const char *filename) {
	strncpy(name, _name, sizeof(name));

	tex = new sf::Texture();
	tex->loadFromFile(filename);
	tex->setSmooth(true);

	spr = new sf::Sprite();
	spr->setTexture(*tex);
	spr->setOrigin(sf::Vector2f(tex->getSize()) / 2.0f);
}

//======================================================================


fired::GameSprite::~GameSprite() {
	delete spr;
	delete tex;
}

//======================================================================


fired::NewGameSprite::NewGameSprite(const char *filename) {
	tex = new sf::Texture();
	tex->loadFromFile(filename);
	tex->setSmooth(true);

	spr = new sf::Sprite();
	spr->setTexture(*tex);
}

//======================================================================


fired::NewGameSprite::~NewGameSprite() {
	delete spr;
	delete tex;
}
