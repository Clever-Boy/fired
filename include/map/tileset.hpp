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
		sf::Texture *maskTex;
		std::vector<sf::Texture*> textures;
		std::vector<sf::Sprite*>  sprites;


		 Tileset();
		~Tileset();

		void addTile(const char *filename);
	};
}

#endif
