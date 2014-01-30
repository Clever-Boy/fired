/***********************************************************************
     * File       : tile.hpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __TILE
#define __TILE


#include "tileset.hpp"


namespace fired {
	struct MapTile {
		int tileset;
		bool isWall;
		bool isPlatform;
	};


	struct Tile {
		sf::Vector2f pos;
		sf::Vector2i index;
		sf::Sprite  *sprite;
		sf::Color    color;
		sf::Color    light;

		int tileset;
		int tile;
		bool isWall;
		bool isPlatform;

		char intensity;
		char absorb;


		void set(int _tileset, bool _isWall, bool _isPlatform, int x, int y);
		void render();

		void setTileset();
		void setTile(int _tile);
	};
}

#endif
