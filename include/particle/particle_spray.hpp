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
		sf::Vector2f pos;
		sf::Vector2f direction;
		sf::Vector2f accel;
		sf::Vector2f normal;
		sf::Color    color;
		float        lifetime;
		float        size;
		float        frequency;
		float        endScale;
		bool         active;


		ParticleSystemSpray(sf::Vector2f _pos, sf::Vector2f _direction, fired::World *_world, sf::Color _color, float _size, float _frequency, float _lifetime, float _endScale, bool _physical);

		bool update();
		void addParticle();
		void stop() { active = false; };
	};
}

#endif

