/***********************************************************************
     * File       : splash.hpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __SPLASH
#define __SPLASH


namespace fired {
	struct ParticleSystemSplash: ParticleSystem {
		sf::RectangleShape *sprite;
		float endScale;


		 ParticleSystemSplash(sf::Vector2f pos, sf::Vector2f direction, fired::World *_world, sf::Color color, float size, int count, float lifetime, float _endScale, bool _physical);
		~ParticleSystemSplash();

		bool update();
	};
}

#endif

