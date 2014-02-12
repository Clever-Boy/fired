/***********************************************************************
     * File       : particle_smoke.hpp
     * Created    : Feb 12, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __PARTICLE_SMOKE
#define __PARTICLE_SMOKE


namespace fired {
	struct ParticleSystemSmoke: ParticleSystemSpray {
		ParticleSystemSmoke(sf::Vector2f pos, sf::Vector2f direction, fired::World *world, float size);
	};
}

#endif

