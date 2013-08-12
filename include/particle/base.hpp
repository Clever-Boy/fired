#ifndef __BASE
#define __BASE


#include <SFML/Graphics.hpp>


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


	class ParticleSystem {
	protected:
		fired::World *world;
		float         life;
		bool          physical;
		sf::Vector2f  accel;

		std::vector<fired::Particle*> particles;


	public:
		virtual ~ParticleSystem();

		virtual bool update();
		void render();
	};
}

#endif
