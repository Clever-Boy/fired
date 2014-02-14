/***********************************************************************
     * File       : resources.hpp
     * Created    : Feb 05, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __RESOURCES
#define __RESOURCES


namespace fired {
	struct Resources {
		struct {
			sf::SoundBuffer *explosion;
		} sounds;


		struct {
			sf::Texture *trashTex;
			sf::Texture *emptyTex;
			sf::Texture *hoverTex;
			sf::Texture *normalTex;

			sf::Sprite *trashSpr;
			sf::Sprite *emptySpr;
			sf::Sprite *hoverSpr;
			sf::Sprite *normalSpr;
		} win;


		struct {
			sf::Texture *coinTex;
			sf::Texture *smokeTex;
			sf::Texture *snowflakeTex;

			sf::Sprite  *coin;
			sf::Sprite  *smoke;
			sf::Sprite  *snowflake;
		} sprites;


		 Resources();
		~Resources();
	};
}

#endif
