#ifndef __CREDITSSCR
#define __CREDITSSCR


#define CREDITSSCR_SPEED 50
#define CREDITSSCR_WIDTH 700


namespace fired {
	class CreditsScr {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;

		std::vector<sf::Text*> credits;
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
