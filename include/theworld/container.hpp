#ifndef __CONTAINER
#define __CONTAINER


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "char.hpp"
#include "theworld.hpp"


namespace fired {
	class Container {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;
		fired::World     *world;

		std::vector<fired::BaseWeapon*>   weapons;
		std::vector<fired::BaseBodypart*> bodyparts;
		std::vector<fired::BaseModel*>    models;
		std::vector<fired::BaseCreature*> creatures;


	public:
		 Container(fired::Game *_game, fired::World *_world);
		~Container();

		fired::BaseAI *getAI(const char *name, fired::Creature *owner);

		void loadWeapons();
		void loadWeapon(const char* filename);
		fired::BaseWeapon *getWeapon(const char* name);

		void loadModels();
		void loadModel(const char* filename);
		fired::BaseModel *getModel(const char* name);

		void loadCreatures();
		void loadCreature(const char* filename);
		fired::BaseCreature *getCreature(const char* name);

		void loadBodyparts();
		void loadBodypartsInDir(const char *dir, fired::BodypartType type);
		void loadBodypart(const char *dir, const char* filename, fired::BodypartType type);
		fired::BaseBodypart *getBodypart(const char* name, fired::BodypartType type);
	};
}

#endif
