#ifndef __STARTSCR
#define __STARTSCR

#define STARTSCR_TIME_DELAY     3.0
#define STARTSCR_TIME_APPEAR    1.0
#define STARTSCR_TIME_DISAPPEAR 2.0


namespace fired {
	class StartScr {
	private:
		std::vector<sf::Texture*> textures;
		std::vector<sf::Sprite*> sprites;

		fired::Game *game;
		float timeOffset;
		int   index;


	public:
		void init(fired::Game *_game);
		void update(float frameClock);
		void render();
		void click(sf::Vector2i pos);
		void processEvent(sf::Event event);
	};
}

#endif
