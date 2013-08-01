#include "game.hpp"

//======================================================================


void fired::Tileset::init() {
	maskTex = new sf::Texture();
	maskTex->loadFromFile("data/img/world/tileset/mask.tga");

	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++) {
			masks.push_back(new sf::Sprite());
			masks.back()->setTexture(*maskTex);
			masks.back()->setTextureRect(sf::IntRect(TILE_SIZE * i, TILE_SIZE * j, TILE_SIZE, TILE_SIZE));
		}

	textures.push_back(NULL);
	sprites.push_back(NULL);

	addTile("data/img/world/tiles/concrete.tga");
	addTile("data/img/world/tiles/greybrick.tga");
	addTile("data/img/world/tiles/redbrick.tga");
	addTile("data/img/world/tiles/warning.tga");
}

//======================================================================


void fired::Tileset::deinit() {
	for (int i = 0; i < masks.size(); delete masks[i], i++);
	for (int i = 1; i < textures.size(); delete textures[i], i++);
	for (int i = 1; i < sprites.size(); delete sprites[i], i++);
	delete maskTex;

	masks.clear();
	sprites.clear();
	textures.clear();
}

//======================================================================


void fired::Tileset::addTile(const char *filename) {
	textures.push_back(new sf::Texture);
	sprites.push_back(new sf::Sprite);

	textures.back()->loadFromFile(filename);
	sprites.back()->setTexture(*textures.back());
}
