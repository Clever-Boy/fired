#ifndef __CREDITSSCR
#define __CREDITSSCR

#define CREDITSSCR_SPEED 100
#define CREDITSSCR_WIDTH 700


namespace fired {
	class CreditsScr {
	private:
		fired::Game *game;
		std::vector<sf::Text*> credits;
		sf::Music *musicTheme;

		float yOffset;

	public:
		void init(fired::Game *_game);
		void deinit();
		void update(float frameClock);
		void render();
		void click(sf::Vector2i pos);
		void processEvent(sf::Event event);
	};
}

#endif
