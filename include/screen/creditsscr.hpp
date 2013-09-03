#ifndef __CREDITSSCR
#define __CREDITSSCR


namespace fired {
	struct CreditsScr : GameScreen {
		std::vector<sf::Text*> credits;
		float yOffset;


		 CreditsScr();
		~CreditsScr();

		void update();
		void render();
		void click(sf::Vector2i pos);
		void processEvent(sf::Event event);
	};
}

#endif
