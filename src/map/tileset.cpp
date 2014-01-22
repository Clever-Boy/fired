/***********************************************************************
     * File       : tileset.cpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Class
     * constructor

***********************************************************************/
fired::Tileset::Tileset() {
	maskTex = new sf::Texture();
	maskTex->loadFromFile("data/img/world/tileset/mask.tga");

	addTile("data/img/world/tiles/concrete.tga");
	addTile("data/img/world/tiles/greybrick.tga");
	addTile("data/img/world/tiles/redbrick.tga");
	addTile("data/img/world/tiles/warning.tga");
}



/***********************************************************************
     * Class
     * destructor

***********************************************************************/
fired::Tileset::~Tileset() {
	deleteList(textures);
	deleteList(sprites);
	delete maskTex;
}



/***********************************************************************
     * Class
     * addTile

***********************************************************************/
void fired::Tileset::addTile(const char *filename) {
	sf::RenderTexture *text = new sf::RenderTexture;
	sf::Texture       *tile = new sf::Texture;
	sf::Sprite        *sprt = new sf::Sprite;
	sf::Sprite        *mask = new sf::Sprite;

	tile->loadFromFile(filename);
	tile->setRepeated(true);

	sprt->setTexture(*tile);
	sprt->setTextureRect(sf::IntRect(0, 0, 64, 64));

	mask->setTexture(*maskTex);

	text->create(64, 64);
	text->draw(*sprt);
	text->draw(*mask);
	text->display();

	textures.push_back(new sf::Texture(text->getTexture()));

	delete text;
	delete tile;
	delete sprt;
	delete mask;


	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++) {
			sprites.push_back(new sf::Sprite());
			sprites.back()->setTexture(*textures.back());
			sprites.back()->setTextureRect(sf::IntRect(TILE_SIZE * i, TILE_SIZE * j, TILE_SIZE, TILE_SIZE));
		}
}
