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
		 CreditsScr(fired::Game *_game);
		~CreditsScr();

		void update();
		void render();
		void click(sf::Vector2i pos);
		void processEvent(sf::Event event);
	};
}

#endif
