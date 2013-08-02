#ifndef __BASE
#define __BASE


#include <SFML/Graphics.hpp>


namespace fired {
	struct Particle {
		float lifetime;
		float life;

		sf::Color           color;
		sf::RectangleShape *sprite;
		sf::Vector2f        pos;
		sf::Vector2f        speed;
		sf::Vector2f        accel;

		bool process(sf::RenderWindow *app);
	};


	class ParticleSystem {
	protected:
		float life;
		sf::Vector2f accel;
		std::vector<fired::Particle*> particles;


	public:
		virtual void init()   {return; };
		virtual bool update() {return false; };
		virtual void deinit() {return; };

		void render(sf::RenderWindow *app);
	};
}

#endif
