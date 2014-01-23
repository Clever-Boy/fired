/***********************************************************************
     * File       : container.hpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CONTAINER
#define __CONTAINER


#include <sqlite3.h>

#include "char.hpp"
#include "sounds.hpp"
#include "map.hpp"


namespace fired {
	struct Container {
		std::vector<fired::BaseWeapon*>   weapons;
		std::vector<fired::BaseArmor*>    armors;
		std::vector<fired::BaseBodypart*> bodyparts;
		std::vector<fired::BaseModel*>    models;
		std::vector<fired::BaseCreature*> creatures;
		std::vector<fired::BaseDecor*>    decors;
		std::vector<fired::BaseItem*>     items;
		std::vector<fired::GameSprite*>   sprites;
		std::vector<fired::GameSound*>    sounds;
		std::vector<fired::Biome*>        biomes;


		 Container();
		~Container();

		fired::BaseAI *getAI(const char *name, fired::Creature *owner, fired::World *world);

		void loadSprites(sqlite3 *db);
		static int loadSprite(void *data, int argc, char **argv, char **azColName);

		void loadSounds(sqlite3 *db);
		static int loadSound(void *data, int argc, char **argv, char **azColName);
		sf::Sound *getSound(const char *name);

		void loadDecors(sqlite3 *db);
		static int loadDecor(void *data, int argc, char **argv, char **azColName);
		fired::BaseDecor *getDecor(const char* name);

		void loadBodyparts(sqlite3 *db);
		static int loadBodypart(void *data, int argc, char **argv, char **azColName);
		fired::BaseBodypart *getBodypart(const char* name, fired::BodypartType type);

		void loadModels(sqlite3 *db);
		static int loadModel(void *data, int argc, char **argv, char **azColName);
		void loadModelBodypart(const char* s, fired::BaseModelBodypart *bodypart, fired::BodypartType type);

		void loadArmors(sqlite3 *db);
		static int loadArmor(void *data, int argc, char **argv, char **azColName);
		int getArmorIndex(const char *name);

		void loadWeapons(sqlite3 *db);
		static int loadWeapon(void *data, int argc, char **argv, char **azColName);
		int getWeaponIndex(const char *name);

		void loadItems(sqlite3 *db);
		static int loadItem(void *data, int argc, char **argv, char **azColName);
		fired::BaseItem *getItem(const char *name);

		void loadCreatures(sqlite3 *db);
		static int loadCreature(void *data, int argc, char **argv, char **azColName);
		void loadCreatureLoot(fired::BaseCreature *current, const char *lootStr);
		fired::BaseCreature *getCreature(const char *name);

		void loadBiomes(sqlite3 *db);
		static int loadBiome(void *data, int argc, char **argv, char **azColName);
		fired::Biome *getBiome(const char *name);
	};
}

#endif
