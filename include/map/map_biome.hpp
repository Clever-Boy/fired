/***********************************************************************
     * File       : map_biome.hpp
     * Created    : Jan 22, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MAP_BIOME
#define __MAP_BIOME


namespace fired {
	struct Biome {
		char name[64];
		char weather[64];
		char intensity;

		sf::Color skyHi;
		sf::Color skyLow;
		sf::Color cloudColor;
		sf::Color lightness;

		sf::Texture        *bgTex;
		sf::RectangleShape *bgSprite;
		float               bgScale;

		fired::Tileset *ground;
		fired::Tileset *brickMain;
		fired::Tileset *brickSecond;
		fired::Tileset *extra;

		std::vector<fired::BaseCreature*> creatures;


		 Biome(const char *bgFile);
		~Biome();
	};
}

#endif
