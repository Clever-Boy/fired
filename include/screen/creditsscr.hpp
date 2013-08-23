#ifndef __CREDITSSCR
#define __CREDITSSCR


namespace fired {
	class CreditsScr : public GameScreen {
	private:
		std::vector<sf::Text*> credits;
		float yOffset;


	public:
		 CreditsScr();
		~CreditsScr();

		void update();
		void render();
		void click(sf::Vector2i pos);
		void processEvent(sf::Event event);
	};
}

#endif
