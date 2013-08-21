#ifndef __CONTAINER
#define __CONTAINER


#include <SFML/Graphics.hpp>
#include "char.hpp"
#include "theworld.hpp"
#include "sprites.hpp"
#include "prototypes.hpp"


namespace fired {
	class Container {
	private:
		fired::World     *world;

		std::vector<fired::BaseWeapon*>   weapons;
		std::vector<fired::BaseBodypart*> bodyparts;
		std::vector<fired::BaseModel*>    models;
		std::vector<fired::BaseCreature*> creatures;
		std::vector<fired::BaseDecor*>    decors;
		std::vector<fired::GameSprite*>   sprites;


	public:
		 Container(fired::World *_world);
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

		void loadDecors();
		void loadDecor(const char* filename);
		fired::BaseDecor *getDecor(const char* name);

		void loadSprites();
		void loadSprite(const char* filename);
		sf::Sprite *getSprite(const char* name);

		void loadBodyparts();
		void loadBodypartsInDir(const char *dir, fired::BodypartType type);
		void loadBodypart(const char *dir, const char* filename, fired::BodypartType type);
		fired::BaseBodypart *getBodypart(const char* name, fired::BodypartType type);
	};
}

#endif
