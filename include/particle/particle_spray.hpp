/***********************************************************************
     * File       : particle_spray.hpp
     * Created    : Feb 11, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __PARTICLE_SPRAY
#define __PARTICLE_SPRAY


namespace fired {
	struct ParticleSystemSpray: ParticleSystem {
		sf::RectangleShape *sprite;
		float endScale;


		 ParticleSystemSpray(sf::Vector2f pos, sf::Vector2f direction, fired::World *_world, sf::Color color, float size, int count, float lifetime, float _endScale, bool _physical);
		~ParticleSystemSpray();

		bool update();
	};
}

#endif

