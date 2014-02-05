/***********************************************************************
     * File       : world_explosion.hpp
     * Created    : Jan 21, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WORLD_EXPLOSION
#define __WORLD_EXPLOSION


namespace fired {
	struct BaseExplosion {
		sf::Texture              *tex;
		std::vector<sf::Sprite*>  spr;
		float                     radius;


		 BaseExplosion(const char *filename);
		~BaseExplosion();
	};


	struct Explosion {
		fired::BaseExplosion *base;
		sf::Vector2f          scale;
		sf::Vector2f          pos;
		float                 lifetime;
		float                 life;


		 Explosion(sf::Vector2f _pos, float radius, float _life);

		bool update();
		void render();
	};
}

#endif
