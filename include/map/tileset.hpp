/***********************************************************************
     * File       : tileset.hpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __TILESET
#define __TILESET


namespace fired {
	struct Tileset {
		int ID;
		sf::Texture *tex;
		std::vector<sf::Sprite*>  sprites;


		 Tileset(int _ID, fired::GameSprite *baseSprite);
		~Tileset();
	};
}

#endif
