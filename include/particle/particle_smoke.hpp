/***********************************************************************
     * File       : particle_smoke.hpp
     * Created    : Feb 11, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __PARTICLE_SMOKE
#define __PARTICLE_SMOKE


namespace fired {
	struct ParticleSystemSmoke: ParticleSystem {
		sf::RectangleShape *sprite;
		float endScale;


		 ParticleSystemSmoke(sf::Vector2f pos, sf::Vector2f direction, fired::World *_world, sf::Color color, float size, int count, float lifetime, float _endScale, bool _physical);
		~ParticleSystemSmoke();

		bool update();
	};
}

#endif

