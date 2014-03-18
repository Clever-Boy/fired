/***********************************************************************
     * File       : map_tileset.hpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MAP_TILESET
#define __MAP_TILESET


namespace fired {
	struct Tileset {
		int          ID;
		char         name[64];
		sf::Texture *tex;
		std::vector<sf::Sprite*> sprites;


		 Tileset(int _ID, fired::GameSprite *baseSprite, bool flat, char *_name);
		~Tileset();
	};
}

#endif
