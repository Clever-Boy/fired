#ifndef __PROTOTYPES
#define __PROTOTYPES

namespace fired {
	class Character;
	class Player;
	class World;
	class BaseWeapon;


	class GameScreen {
	public:
		virtual ~GameScreen()                {};
		virtual void update()                {};
		virtual void processEvent(sf::Event) {};
	};
}

#endif
