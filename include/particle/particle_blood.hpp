/***********************************************************************
     * File       : particle_blood.hpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __PARTICLE_BLOOD
#define __PARTICLE_BLOOD


namespace fired {
	struct ParticleSystemBlood: ParticleSystemSplash {
		ParticleSystemBlood(sf::Vector2f pos, sf::Vector2f direction, fired::World *_world, int bloodCount) : ParticleSystemSplash(pos, direction, _world, sf::Color(150, 0, 0, 155), 3, bloodCount, 17.0, 0.5, true) {};
	};
}

#endif

