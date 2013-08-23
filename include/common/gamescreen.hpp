#ifndef __GAMESCREEN
#define __GAMESCREEN

namespace fired {
	class GameScreen {
	public:
		virtual ~GameScreen()                {};
		virtual void update()                {};
		virtual void processEvent(sf::Event) {};
	};
}

#endif
