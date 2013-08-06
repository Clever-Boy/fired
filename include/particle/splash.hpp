#ifndef __SPLASH
#define __SPLASH


namespace fired {
	class ParticleSystemSplash: public ParticleSystem {
	private:
		sf::RectangleShape *sprite;


	public:
		void init(sf::Vector2f pos, sf::Vector2f direction, sf::Color color, float size);

		void deinit();
		bool update(sf::RenderWindow *app);
	};
}

#endif

