#include "game.hpp"

//======================================================================


void fired::Tileset::init(const char *textureFile) {
	sf::Image *image = new sf::Image();
	image->loadFromFile(textureFile);
	image->createMaskFromColor(sf::Color(255, 0, 255, 255));

	texture = new sf::Texture();
	texture->loadFromImage(*image);
	delete image;

	for (int j = 0; j < 12; j++)
		for (int i = 0; i < 16; i++) {
			tiles.push_back(new sf::Sprite());
			tiles.back()->setTexture(*texture);
			tiles.back()->setTextureRect(sf::IntRect(TILE_SIZE_ORIGIN * i, TILE_SIZE_ORIGIN * j, TILE_SIZE_ORIGIN, TILE_SIZE_ORIGIN));
			tiles.back()->setScale(TILE_SIZE / TILE_SIZE_ORIGIN, TILE_SIZE / TILE_SIZE_ORIGIN);
		}
}

//======================================================================


void fired::Tileset::deinit() {
	for (int i = 0; i < tiles.size(); delete tiles[i], i++);
	tiles.clear();

	delete texture;
}

