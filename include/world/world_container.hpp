/***********************************************************************
     * File       : world_container.hpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WORLD_CONTAINER
#define __WORLD_CONTAINER


#include <sqlite3.h>

#include "char.hpp"
#include "world_sound.hpp"
#include "map.hpp"


namespace fired {
	struct Container {
		std::vector<fired::BaseWeapon*>      weapons;
		std::vector<fired::BaseArmor*>       armors;
		std::vector<fired::BaseBodypart*>    bodyparts;
		std::vector<fired::BaseModel*>       models;
		std::vector<fired::BaseCreature*>    creatures;
		std::vector<fired::BaseDecor*>       decors;
		std::vector<fired::BaseLightSource*> lights;
		std::vector<fired::BaseItem*>        items;
		std::vector<fired::BaseExplosion*>   explosions;
		std::vector<fired::GameSprite*>      sprites;
		std::vector<fired::GameSound*>       sounds;
		std::vector<fired::Tileset*>         tilesets;
		std::vector<fired::Biome*>           biomes;


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
		unsigned int getDecor(const char* name);

		void loadLights(sqlite3 *db);
		static int loadLight(void *data, int argc, char **argv, char **azColName);
		unsigned int getLight(const char* name);

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
		int getItemIndex(const char *name);

		void loadCreatures(sqlite3 *db);
		static int loadCreature(void *data, int argc, char **argv, char **azColName);
		void loadCreatureLoot(fired::BaseCreature *current, const char *lootStr);
		fired::BaseCreature *getCreature(const char *name);

		void loadTilesets(sqlite3 *db);
		static int loadTileset(void *data, int argc, char **argv, char **azColName);

		void loadBiomes(sqlite3 *db);
		static int loadBiome(void *data, int argc, char **argv, char **azColName);
		fired::Biome *getBiome(const char *name);

		void loadExplosions(sqlite3 *db);
		static int loadExplosion(void *data, int argc, char **argv, char **azColName);
		fired::BaseExplosion *getExplosion();
	};
}

#endif
