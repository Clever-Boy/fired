/***********************************************************************
     * File       : particle_sparc.hpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __PARTICLE_SPARK
#define __PARTICLE_SPARK


namespace fired {
	struct ParticleSystemSparc: ParticleSystemSplash {
		ParticleSystemSparc(sf::Vector2f pos, sf::Vector2f direction, fired::World *_world) : ParticleSystemSplash(pos, direction, _world, sf::Color(239, 231, 145, 255), 2, 20, 0.3, 0, false) {};
	};
}

#endif

