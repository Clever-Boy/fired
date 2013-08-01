#ifndef __TILE
#define __TILE


#define TILE_SIZE        16.0
#define TILE_SIZE_ORIGIN 32.0


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	struct MapTile {
		int tileset;
		bool isWall;
	};


	class Tile {
	private:
		fired::Tileset *tileset;

		sf::Vector2f pos;
		sf::Sprite  *sprite;
		sf::Color    color;
		int tilesetIdx;
		int tile;
		bool isWall;


	public:
		void init(int _tileset, bool _isWall, int x, int y);
		void deinit();
		void render(sf::RenderWindow *app);

		void setTileset(fired::Tileset *_tileset);
		void setTile(int _tile);
		int  getIndex() { return tilesetIdx; };
		bool isSolid()  { return isWall; };
	};
}

#endif
