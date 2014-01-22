/***********************************************************************
     * File       : decor.hpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __DECOR
#define __DECOR


namespace fired {
	struct MapDecor {
		char name[64];
		sf::Vector2f pos;


		MapDecor() {};
		MapDecor(const char *_name, sf::Vector2f _pos);
	};



	struct BaseDecor {
		char name[64];
		fired::GameSprite *sprite;
		sf::Vector2f       size;


		 BaseDecor(const char *_name, sf::Vector2f _size, fired::GameSprite *_sprite);
	};



	struct Decor {
		fired::BaseDecor *base;

		sf::Vector2f      pos;
		sf::Sprite       *sprite;
		sf::FloatRect     rect;
		sf::Color         color;


		Decor(fired::BaseDecor *base, sf::Vector2f _pos);
		void render();
	};
}

#endif
