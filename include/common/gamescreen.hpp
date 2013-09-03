#ifndef __GAMESCREEN
#define __GAMESCREEN

namespace fired {
	struct GameScreen {
		virtual ~GameScreen()                {};
		virtual void update()                {};
		virtual void processEvent(sf::Event) {};
	};
}

#endif
