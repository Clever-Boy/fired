/***********************************************************************
     * File       : particle_sparc.hpp
     * Created    : Feb 12, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __PARTICLE_SPARC
#define __PARTICLE_SPARC


namespace fired {
	struct ParticleSystemSparc: ParticleSystemSplash {
		ParticleSystemSparc(sf::Vector2f pos, sf::Vector2f direction, fired::World *_world) : ParticleSystemSplash(pos, direction, _world, sf::Color(239, 231, 145, 255), 2, 20, 0.3, 0, false) {};
	};
}

#endif

