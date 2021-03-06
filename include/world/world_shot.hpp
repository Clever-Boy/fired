/***********************************************************************
     * File       : world_shot.hpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WORLD_SHOT
#define __WORLD_SHOT


namespace fired {
	struct Shot;
	struct BroadShot;
	struct MeleeShot;
}


#include "char.hpp"


namespace fired {
	struct Shot {
		sf::Vector2f pos;
		sf::Vector2f origin;
		sf::Vector2i index;
		sf::Vector2f velocity;
		float        angle;
		float        knockback;
		float        leftToFly;
		float        explosionRadius;

		bool         farAway;
		bool         explosive;
		int          damage;
		int          fraction;

		sf::VertexArray             line;
		fired::GameSprite          *sprite;
		fired::Character           *owner;
		fired::ParticleSystemSpray *tracer;
		fired::World               *world;


		 Shot(fired::Character *_owner, fired::World *_world);
		~Shot();

		bool update();
		void render();
	};


	struct BroadShot {
		sf::FloatRect shot;
		sf::Vector2f  normal;
		int           damage;
		int           fraction;
		float         knockback;

		fired::Character *owner;


		BroadShot(sf::FloatRect _shot, sf::Vector2f _normal, fired::Character *_owner);
	};


	struct MeleeShot {
		sf::Vector2f  pos;
		sf::Vector2f  direction;
		int           damage;
		int           fraction;
		float         knockback;

		fired::Character *owner;


		MeleeShot(sf::Vector2f _pos, sf::Vector2f _direction, fired::Character *_owner);
	};
}

#endif
