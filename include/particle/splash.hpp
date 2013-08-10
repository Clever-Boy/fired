#ifndef __SPLASH
#define __SPLASH


namespace fired {
	class ParticleSystemSplash: public ParticleSystem {
	private:
		sf::RectangleShape *sprite;
		float endScale;


	public:
		void init(sf::Vector2f pos, sf::Vector2f direction, fired::World *_world, sf::Color color, float size, int count, float lifetime, float _endScale, bool _physical);

		~ParticleSystemSplash();
		bool update(sf::RenderWindow *app);
	};
}

#endif

