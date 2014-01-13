#ifndef __CONTAINER
#define __CONTAINER


#include <sqlite3.h>

#include "char.hpp"
#include "sprites.hpp"
#include "map.hpp"


namespace fired {
	struct Container {
		fired::World     *world;

		std::vector<fired::BaseWeapon*>   weapons;
		std::vector<fired::BaseArmor*>    armors;
		std::vector<fired::BaseBodypart*> bodyparts;
		std::vector<fired::BaseModel*>    models;
		std::vector<fired::BaseCreature*> creatures;
		std::vector<fired::BaseDecor*>    decors;
		std::vector<fired::GameSprite*>   sprites;


		 Container(fired::World *_world);
		~Container();

		fired::BaseAI *getAI(const char *name, fired::Creature *owner);

		void loadWeapons();
		void loadWeapon(const char* filename);
		fired::BaseWeapon *getWeapon(const char* name);

		void loadArmors();
		void loadArmorsInDir(const char *dir, fired::ArmorClass type);
		void loadArmor(const char* filename, fired::ArmorClass type);
		fired::BaseArmor *getArmor(const char* name, fired::ArmorClass type);

		void loadModels();
		void loadModelBodypart(const char* s, fired::BaseModelBodypart *bodypart, fired::BodypartType type);
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

		//------------------------- SQLite -----------------------------

		std::vector<fired::NewGameSprite*> _sprites;

		void NewLoad();
		void _loadSprites(sqlite3 *db);
		static int _loadSprite(void *data, int argc, char **argv, char **azColName);

	};
}

#endif
