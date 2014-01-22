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
		sf::Sprite  *sprite;
		sf::Color    color;

		int tileset;
		int tile;
		bool isWall;
		bool isPlatform;


		void set(int _tileset, bool _isWall, bool _isPlatform, int x, int y);
		void render();

		void setTileset(fired::Tileset *_tileset);
		void setTile(int _tile);
	};
}

#endif
