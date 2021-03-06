/***********************************************************************
     * File       : particle_base.hpp
     * Created    : Aug 01, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __PARTICLE_BASE
#define __PARTICLE_BASE


namespace fired {
	struct Particle {
		float lifetime;
		float life;
		float scale;

		sf::Color           color;
		sf::RectangleShape *sprite;
		sf::Vector2f        pos;
		sf::Vector2f        speed;
		sf::Vector2f        accel;


		bool process(fired::World *world, bool physical);
	};


	struct ParticleSystem {
		fired::World       *world;
		sf::RectangleShape *sprite;
		sf::Vector2f        accel;
		float               life;
		bool                physical;

		std::vector<fired::Particle*> particles;


		virtual ~ParticleSystem();

		virtual bool update();
		void render();
	};
}

#endif
