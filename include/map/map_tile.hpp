/***********************************************************************
     * File       : map_tile.hpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MAP_TILE
#define __MAP_TILE


#include "map_tileset.hpp"


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
		sf::Sprite  *spriteBack;
		sf::Color    color;
		sf::Color    light;

		int  tileset;
		int  tile;
		int  tileBack;
		bool isWall;
		bool isPlatform;

		char intensity;
		char absorb;


		void set(int _tileset, bool _isWall, bool _isPlatform, int x, int y);
		void render();
		void renderWall();
		void renderBack();

		void setTileset();
		void setTile(int _tile);
		void setTileBack(int _tile);
	};
}

#endif
