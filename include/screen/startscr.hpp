#ifndef __STARTSCR
#define __STARTSCR


#define STARTSCR_TIME_DELAY     4.0
#define STARTSCR_TIME_APPEAR    1.5
#define STARTSCR_TIME_DISAPPEAR 2.5


namespace fired {
	class StartScr {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;

		std::vector<sf::Texture*> textures;
		std::vector<sf::Sprite*> sprites;

		float timeOffset;
		int   index;


	public:
		void init(fired::Game *_game);
		void deinit();
		void update();
		void render();
		void processEvent(sf::Event event);
	};
}

#endif
