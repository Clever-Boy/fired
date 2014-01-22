/***********************************************************************
     * File       : shot.hpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __SHOT
#define __SHOT


namespace fired {
	struct Shot;
	struct BroadShot;
	struct MeleeShot;
}


#include "char.hpp"


namespace fired {
	struct Shot {
		sf::Vector2f pos;
		sf::Vector2f velocity;
		float        angle;
		int          damage;
		float        knockback;
		float        leftToFly;

		sf::VertexArray    line;
		fired::GameSprite *sprite;
		fired::Character  *owner;
		fired::World      *world;


		 Shot(sf::Vector2f _pos, float _angle, float speed, fired::Character *_owner, fired::GameSprite *_sprite, fired::World *_world);

		bool update();
		void render();
	};


	struct BroadShot {
		sf::FloatRect shot;
		sf::Vector2f  normal;
		int           damage;
		float         knockback;

		fired::Character *owner;


		BroadShot(sf::FloatRect _shot, sf::Vector2f _normal, fired::Character *_owner);
	};


	struct MeleeShot {
		sf::Vector2f  pos;
		sf::Vector2f  direction;
		int           damage;
		float         knockback;

		fired::Character *owner;


		MeleeShot(sf::Vector2f _pos, sf::Vector2f _direction, fired::Character *_owner);
	};
}

#endif
