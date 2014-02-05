/***********************************************************************
     * File       : world_sprite.hpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WORLD_SPRITE
#define __WORLD_SPRITE


namespace fired {
	struct GameSprite {
		sf::Sprite   *spr;
		sf::Texture  *tex;
		sf::Vector2f  size;


		 GameSprite(const char *filename);
		~GameSprite();
	};
}

#endif
