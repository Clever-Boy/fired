#ifndef __PROTOTYPES
#define __PROTOTYPES


namespace fired {
	class Game;
	class Settings;
	class Character;
	class Player;
	class Camera;
	class World;
	class Keyboard;
	class Mouse;
	class Handlers;
	class MainMenu;
	class StartScr;
	class CreditsScr;
	class Tileset;
	class BaseWeapon;
	class BaseCreature;
	class Creature;
	class BaseAI;


	typedef void (Handlers::*Handler)(void);


	class GameScreen {
	public:
		virtual ~GameScreen()                {};
		virtual void update()                {};
		virtual void processEvent(sf::Event) {};
	};
}

#endif
