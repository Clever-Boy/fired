/***********************************************************************
     * File       : decor.hpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __DECOR
#define __DECOR


namespace fired {
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


		Decor(fired::BaseDecor *_base, sf::Vector2f _pos);
		void render();
	};
}

#endif
