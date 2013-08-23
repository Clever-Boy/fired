#ifndef __STARTSCR
#define __STARTSCR


namespace fired {
	class StartScr : public GameScreen {
	private:
		std::vector<sf::Texture*> textures;
		std::vector<sf::Sprite*> sprites;

		float        timeOffset;
		unsigned int index;


	public:
		 StartScr();
		~StartScr();

		void update();
		void render();
		void processEvent(sf::Event event);
	};
}

#endif
