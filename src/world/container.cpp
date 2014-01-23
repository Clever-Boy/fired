/***********************************************************************
     * File       : container.cpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Container
     * constructor

***********************************************************************/
fired::Container::Container() {
	sqlite3 *db;
	sqlite3_open("data/database.sqlite", &db);

	loadSprites(db);
	loadSounds(db);
	loadDecors(db);
	loadBodyparts(db);
	loadModels(db);
	loadArmors(db);
	loadWeapons(db);
	loadItems(db);
	loadCreatures(db);
	loadTilesets(db);
	loadBiomes(db);

	sqlite3_close(db);
}



/***********************************************************************
     * Container
     * destructor

***********************************************************************/
fired::Container::~Container() {
	deleteList(biomes);
	deleteList(tilesets);
	deleteList(items);
	deleteList(weapons);
	deleteList(armors);
	deleteList(bodyparts);
	deleteList(models);
	deleteList(creatures);
	deleteList(decors);
	deleteList(sprites);
	deleteList(sounds);
}



/***********************************************************************
     * Container
     * getAI

***********************************************************************/
fired::BaseAI *fired::Container::getAI(const char *name, fired::Creature *owner, fired::World *world) {
	if (!strcmp(name, "idle")) return new fired::IdleAI(owner, world);
	if (!strcmp(name, "basic")) return new fired::BasicAI(owner, world);

	return new fired::BaseAI();
}



/***********************************************************************
     * Container
     * loadSprites

***********************************************************************/
void fired::Container::loadSprites(sqlite3 *db) {
	char *zErrMsg = 0;

	if (sqlite3_exec(db, "SELECT Path FROM Sprites",
	                     loadSprite, this, &zErrMsg) != SQLITE_OK)
		printf("SQL error: %s\n", zErrMsg);
}



/***********************************************************************
     * Container
     * loadSprite

***********************************************************************/
int fired::Container::loadSprite(void *data, int, char **argv, char **) {
	((fired::Container *) data)->sprites.push_back(new fired::GameSprite(argv[0]));
	return 0;
}



/***********************************************************************
     * Container
     * loadSounds

***********************************************************************/
void fired::Container::loadSounds(sqlite3 *db) {
	char *zErrMsg = 0;

	if (sqlite3_exec(db, "SELECT Name, Path FROM Sounds",
	                     loadSound, this, &zErrMsg) != SQLITE_OK)
		printf("SQL error: %s\n", zErrMsg);
}



/***********************************************************************
     * Container
     * loadSound

***********************************************************************/
int fired::Container::loadSound(void *data, int, char **argv, char **) {
	((fired::Container *) data)->sounds.push_back(new fired::GameSound(argv[1], argv[0]));
	return 0;
}



/***********************************************************************
     * Container
     * getSound

***********************************************************************/
sf::Sound* fired::Container::getSound(const char *name) {
	for (unsigned int i = 0; i < sounds.size(); i++)
		if (!strcmp(name, sounds[i]->name)) return sounds[i]->snd;

	return NULL;
}



/***********************************************************************
     * Container
     * loadDecors

***********************************************************************/
void fired::Container::loadDecors(sqlite3 *db) {
	char *zErrMsg = 0;

	if (sqlite3_exec(db, "SELECT Decors.*, Sprites.ID "
	                     "FROM Decors, Sprites "
	                     "WHERE Sprites.Name = Decors.Sprite",
	                     loadDecor, this, &zErrMsg) != SQLITE_OK)
		printf("SQL error: %s\n", zErrMsg);
}



/***********************************************************************
     * Container
     * loadDecor

***********************************************************************/
int fired::Container::loadDecor(void *data, int, char **argv, char **) {
	sf::Vector2f size;
	sscanf(argv[2], "%f,%f", &size.x, &size.y);
	((fired::Container *) data)->decors.push_back(new fired::BaseDecor(argv[1], size, ((fired::Container *) data)->sprites[atoi(argv[4])]));
	return 0;
}



/***********************************************************************
     * Container
     * getDecor

***********************************************************************/
fired::BaseDecor* fired::Container::getDecor(const char *name) {
	for (unsigned int i = 0; i < decors.size(); i++)
		if (!strcmp(name, decors[i]->name)) return decors[i];

	return NULL;
}



/***********************************************************************
     * Container
     * loadBodyparts

***********************************************************************/
void fired::Container::loadBodyparts(sqlite3 *db) {
	char *zErrMsg = 0;

	if (sqlite3_exec(db, "SELECT Bodyparts.Name, Bodyparts.BodypartType, Bodyparts.Origin, Sprites.ID "
	                     "FROM Bodyparts, Sprites "
	                     "WHERE Sprites.Name = Bodyparts.Sprite",
	                     loadBodypart, this, &zErrMsg) != SQLITE_OK)
		printf("SQL error: %s\n", zErrMsg);
}



/***********************************************************************
     * Container
     * loadBodypart

***********************************************************************/
int fired::Container::loadBodypart(void *data, int, char **argv, char **) {
	((fired::Container *) data)->bodyparts.push_back(new fired::BaseBodypart);
	fired::BaseBodypart *current = ((fired::Container *) data)->bodyparts.back();

	strcpy(current->name, argv[0]);

	if (!strcmp(argv[1], "arms"  )) current->type = bptArms;
	if (!strcmp(argv[1], "head"  )) current->type = bptHead;
	if (!strcmp(argv[1], "hair"  )) current->type = bptHair;
	if (!strcmp(argv[1], "body"  )) current->type = bptBody;
	if (!strcmp(argv[1], "legs"  )) current->type = bptLegs;
	if (!strcmp(argv[1], "shoe"  )) current->type = bptShoe;
	if (!strcmp(argv[1], "fist"  )) current->type = bptFist;
	if (!strcmp(argv[1], "weapon")) current->type = bptWeapon;

	sscanf(argv[2], "%f,%f", &current->origin.x, &current->origin.y);
	current->sprite = ((fired::Container *) data)->sprites[atoi(argv[3])]->spr;
	current->size   = sf::Vector2f(((fired::Container *) data)->sprites[atoi(argv[3])]->tex->getSize());
	return 0;
}



/***********************************************************************
     * Container
     * getBodypart

***********************************************************************/
fired::BaseBodypart* fired::Container::getBodypart(const char* name, fired::BodypartType type) {
	for (unsigned int i = 0; i < bodyparts.size(); i++)
		if (!strcmp(name, bodyparts[i]->name) && type == bodyparts[i]->type) return bodyparts[i];

	return NULL;
}



/***********************************************************************
     * Container
     * loadModels

***********************************************************************/
void fired::Container::loadModels(sqlite3 *db) {
	char *zErrMsg = 0;

	if (sqlite3_exec(db, "SELECT * FROM Models",
	                     loadModel, this, &zErrMsg) != SQLITE_OK)
		printf("SQL error: %s\n", zErrMsg);
}



/***********************************************************************
     * Container
     * loadModelBodypart

***********************************************************************/
void fired::Container::loadModelBodypart(const char* s, fired::BaseModelBodypart *bodypart, fired::BodypartType type) {
		char field[128];

		sscanf(s, "%[^,],(%hhu,%hhu,%hhu,%hhu),(%f,%f)\n", field, &bodypart->color.r, &bodypart->color.g, &bodypart->color.b, &bodypart->color.a, &bodypart->offset.x, &bodypart->offset.y);
		bodypart->part = getBodypart(field, type);
}



/***********************************************************************
     * Container
     * loadModel

***********************************************************************/
int fired::Container::loadModel(void *data, int, char **argv, char **) {
	char field[128];

	if (!strcmp(argv[1], "humanoid")) {
		fired::BaseModelHumanoid *model = new fired::BaseModelHumanoid;
		model->type = mtHumanoid;

		sscanf(argv[3], "%f,%f\n", &model->size.x, &model->size.y);
		sscanf(argv[4], "%f,%f\n", &model->weaponOffset.x, &model->weaponOffset.y);

		sscanf(strstr(argv[5], "legsf"), "legsf=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partLegsF, bptLegs);
		sscanf(strstr(argv[5], "legsb"), "legsb=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partLegsB, bptLegs);
		sscanf(strstr(argv[5], "shoef"), "shoef=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partShoeF, bptShoe);
		sscanf(strstr(argv[5], "shoeb"), "shoeb=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partShoeB, bptShoe);
		sscanf(strstr(argv[5], "fistf"), "fistf=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partFistF, bptFist);
		sscanf(strstr(argv[5], "fistb"), "fistb=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partFistB, bptFist);
		sscanf(strstr(argv[5], "arms" ), "arms=%s\n" , field); ((fired::Container *) data)->loadModelBodypart(field, &model->partArms , bptArms);
		sscanf(strstr(argv[5], "hair" ), "hair=%s\n" , field); ((fired::Container *) data)->loadModelBodypart(field, &model->partHair , bptHair);
		sscanf(strstr(argv[5], "head" ), "head=%s\n" , field); ((fired::Container *) data)->loadModelBodypart(field, &model->partHead , bptHead);
		sscanf(strstr(argv[5], "body" ), "body=%s\n" , field); ((fired::Container *) data)->loadModelBodypart(field, &model->partBody , bptBody);

		((fired::Container *) data)->models.push_back(model);
	}

	return 0;
}



/***********************************************************************
     * Container
     * loadArmors

***********************************************************************/
void fired::Container::loadArmors(sqlite3 *db) {
	char *zErrMsg = 0;

	if (sqlite3_exec(db, "SELECT Armors.ArmorType, Armors.Caption, Armors.Armor, Armors.Color, Bodyparts.ID, Armors.Extra, Armors.Name "
	                     "FROM Armors, Bodyparts "
	                     "WHERE Armors.ArmorType = Bodyparts.BodypartType "
	                     "AND Armors.Model = Bodyparts.Name",
	                     loadArmor, this, &zErrMsg) != SQLITE_OK)
		printf("SQL error: %s\n", zErrMsg);
}



/***********************************************************************
     * Container
     * loadArmor

***********************************************************************/
int fired::Container::loadArmor(void *data, int, char **argv, char **) {
	((fired::Container *) data)->armors.push_back(new fired::BaseArmor);
	fired::BaseArmor *current = ((fired::Container *) data)->armors.back();

	strcpy(current->caption, argv[1]);
	strcpy(current->name   , argv[6]);

	if (!strcmp(argv[0], "arms"  )) current->type = acArms;
	if (!strcmp(argv[0], "hair"  )) current->type = acHelm;
	if (!strcmp(argv[0], "body"  )) current->type = acBody;
	if (!strcmp(argv[0], "legs"  )) current->type = acLegs;
	if (!strcmp(argv[0], "shoe"  )) current->type = acShoe;
	if (!strcmp(argv[0], "fist"  )) current->type = acFist;

	current->armor = atoi(argv[2]);
	current->base  = ((fired::Container *) data)->bodyparts[atoi(argv[4])];

	sscanf(argv[3], "%hhu,%hhu,%hhu,%hhu", &current->color.r, &current->color.g, &current->color.b, &current->color.a);
	return 0;
}



/***********************************************************************
     * Container
     * getArmorIndex

***********************************************************************/
int fired::Container::getArmorIndex(const char *name) {
	for (unsigned int i = 0; i < armors.size(); i++)
		if (!strcmp(name, armors[i]->name)) return i;

	return -1;
}



/***********************************************************************
     * Container
     * loadWeapons

***********************************************************************/
void fired::Container::loadWeapons(sqlite3 *db) {
	char *zErrMsg = 0;

	if (sqlite3_exec(db, "SELECT Weapons.*, Sprites.ID, Bodyparts.ID "
	                     "FROM Weapons "
	                     "LEFT OUTER JOIN Sprites ON Weapons.ShotSprite = Sprites.Name "
	                     "LEFT OUTER JOIN Bodyparts ON Weapons.Model = Bodyparts.Name "
	                     "WHERE (Bodyparts.BodypartType = 'weapon' OR Bodyparts.ID is NULL)",
	                     loadWeapon, this, &zErrMsg) != SQLITE_OK)
		printf("SQL error: %s\n", zErrMsg);
}



/***********************************************************************
     * Container
     * loadWeapon

***********************************************************************/
int fired::Container::loadWeapon(void *data, int, char **argv, char **){
	((fired::Container *) data)->weapons.push_back(new fired::BaseWeapon);
	fired::BaseWeapon *current = ((fired::Container *) data)->weapons.back();

	strcpy(current->name   , argv[1]);
	strcpy(current->caption, argv[2]);

	sscanf(argv[4], "%d", &current->damage);
	sscanf(argv[5], "%f", &current->range);
	sscanf(argv[6], "%f", &current->cooldown);
	sscanf(argv[7], "%f", &current->knockback);
	sscanf(argv[8], "%d", &current->automatic);

	if (!strcmp(argv[9], "broad" )) current->type = WEAPON_TYPE_BROAD;
	if (!strcmp(argv[9], "melee" )) current->type = WEAPON_TYPE_MELEE;
	if (!strcmp(argv[9], "ranged")) current->type = WEAPON_TYPE_RANGED;

	if (argv[12] && (strlen(argv[12]) > 0)) sscanf(argv[12], "%f", &current->speed);

	if (argv[10] && (strlen(argv[10]) > 0)) current->shotSound  = ((fired::Container *) data)->getSound(argv[10]);
	else current->shotSound = NULL;

	if (argv[13] && (strlen(argv[13]) > 0)) current->shotSprite = ((fired::Container *) data)->sprites[atoi(argv[13])];
	else current->shotSprite = NULL;

	if (argv[14] && (strlen(argv[14]) > 0)) current->bodypart   = ((fired::Container *) data)->bodyparts[atoi(argv[14])];
	else current->bodypart = NULL;

	return 0;
}



/***********************************************************************
     * Container
     * getWeaponIndex

***********************************************************************/
int fired::Container::getWeaponIndex(const char *name) {
	for (unsigned int i = 0; i < weapons.size(); i++)
		if (!strcmp(name, weapons[i]->name)) return i;

	return -1;
}



/***********************************************************************
     * Container
     * loadItems

***********************************************************************/
void fired::Container::loadItems(sqlite3 *db) {
	char *zErrMsg = 0;

	if (sqlite3_exec(db, "SELECT Items.*, Sprites.ID "
	                     "FROM Items, Sprites "
	                     "WHERE Sprites.Name = Items.Icon",
	                     loadItem, this, &zErrMsg) != SQLITE_OK)
		printf("SQL error: %s\n", zErrMsg);
}



/***********************************************************************
     * Container
     * loadItem

***********************************************************************/
int fired::Container::loadItem(void *data, int, char **argv, char **) {
	((fired::Container *) data)->items.push_back(new fired::BaseItem);
	fired::BaseItem *current = ((fired::Container *) data)->items.back();

	strcpy(current->name, argv[1]);
	if (argv[6]) strcpy(current->tip , argv[6]);
	current->sprite = ((fired::Container *) data)->sprites[atoi(argv[7])];

	if (argv[5]) current->maxStack = atoi(argv[5]);
	else         current->maxStack = 0;

	if (!strcmp(argv[3], "armor" )) current->type = itArmor;
	if (!strcmp(argv[3], "weapon")) current->type = itWeapon;

	switch (current->type) {
		case itAny:
			break;

		case itArmor:
			current->UID = ((fired::Container *) data)->getArmorIndex(argv[4]);
			break;

		case itWeapon:
			current->UID = ((fired::Container *) data)->getWeaponIndex(argv[4]);
			break;
	}

	return 0;
}



/***********************************************************************
     * Container
     * getItem

***********************************************************************/
fired::BaseItem *fired::Container::getItem(const char *name) {
	for (unsigned int i = 0; i < items.size(); i++)
		if (!strcmp(name, items[i]->name)) return items[i];

	return NULL;
}



/***********************************************************************
     * Container
     * loadCreatures

***********************************************************************/
void fired::Container::loadCreatures(sqlite3 *db) {
	char *zErrMsg = 0;

	if (sqlite3_exec(db, "SELECT Creatures.*, Models.ID, Weapons.ID "
	                     "FROM Creatures, Weapons, Models "
	                     "WHERE Creatures.Model = Models.ModelName "
	                     "AND Creatures.Weapon = Weapons.Name",
	                     loadCreature, this, &zErrMsg) != SQLITE_OK)
		printf("SQL error: %s\n", zErrMsg);
}



/***********************************************************************
     * Container
     * loadCreatureLoot

***********************************************************************/
void fired::Container::loadCreatureLoot(fired::BaseCreature *current, const char *lootStr) {
	char         name[64];
	unsigned int minCount;
	unsigned int maxCount;
	float        probability;

	sscanf(lootStr, "(%[^)]),(%u,%u),%f\n", name, &minCount, &maxCount, &probability);
	current->loot.push_back(new fired::LootItem(getItem(name), minCount, maxCount, probability));
}



/***********************************************************************
     * Container
     * loadCreature

***********************************************************************/
int fired::Container::loadCreature(void *data, int, char **argv, char **) {
	((fired::Container *) data)->creatures.push_back(new fired::BaseCreature);
	fired::BaseCreature *current = ((fired::Container *) data)->creatures.back();

	strcpy(current->name, argv[1]);
	strcpy(current->ai  , argv[2]);

	if (!strcmp(argv[3], "player"))  current->fraction = FIRED_FRACTION_PLAYER;
	if (!strcmp(argv[3], "soldier")) current->fraction = FIRED_FRACTION_SOLDIER;

	sscanf(argv[5] , "%f", &current->modelScale);
	sscanf(argv[7] , "%d", &current->stats.armor);
	sscanf(argv[8] , "%f", &current->stats.speed);
	sscanf(argv[9] , "%f", &current->stats.accel);
	sscanf(argv[10], "%f", &current->stats.jump);
	sscanf(argv[11], "%f", &current->stats.aimrange);
	sscanf(argv[12], "%d", &current->stats.maxHP);

	current->model  = ((fired::Container *) data)->models[atoi(argv[14])];
	current->weapon = ((fired::Container *) data)->weapons[atoi(argv[15])];

	if (argv[13]) {
		char *token = strtok(argv[13], "\n");

		while (token) {
			((fired::Container *) data)->loadCreatureLoot(current, token);
			token = strtok(NULL, "\n");
		}
	}

	return 0;
}



/***********************************************************************
     * Container
     * getCreature

***********************************************************************/
fired::BaseCreature *fired::Container::getCreature(const char *name) {
	for (unsigned int i = 0; i < creatures.size(); i++)
		if (!strcmp(name, creatures[i]->name)) return creatures[i];

	return NULL;
}



/***********************************************************************
     * Container
     * loadTilesets

***********************************************************************/
void fired::Container::loadTilesets(sqlite3 *db) {
	char *zErrMsg = 0;

	if (sqlite3_exec(db, "SELECT Tiles.ID, Sprites.ID FROM Tiles, Sprites "
	                     "WHERE Tiles.Sprite = Sprites.Name",
	                     loadTileset, this, &zErrMsg) != SQLITE_OK)
		printf("SQL error: %s\n", zErrMsg);
}



/***********************************************************************
     * Container
     * loadTileset

***********************************************************************/
int fired::Container::loadTileset(void *data, int, char **argv, char **) {
	((fired::Container *) data)->tilesets.push_back(new fired::Tileset(atoi(argv[0]), ((fired::Container *) data)->sprites[atoi(argv[1])]));
	return 0;
}



/***********************************************************************
     * Container
     * loadBiomes

***********************************************************************/
void fired::Container::loadBiomes(sqlite3 *db) {
	char *zErrMsg = 0;

	if (sqlite3_exec(db, "SELECT Biomes.ID, Biomes.Name, Biomes.SkyGradientHi, "
	                     "Biomes.SkyGradientLow, Biomes.Weather, Biomes.Lightness, Biomes.Background, "
	                     "Biomes.CloudColor, T1.ID, T2.ID, T3.ID, T4.ID FROM Biomes "
	                     "LEFT JOIN Tiles T1 ON T1.Name = Biomes.TileGround "
	                     "LEFT JOIN Tiles T2 ON T2.Name = Biomes.TileBricksMain "
	                     "LEFT JOIN Tiles T3 ON T3.Name = Biomes.TileBricksSecond "
	                     "LEFT JOIN Tiles T4 ON T4.Name = Biomes.TileExtra",
	                     loadBiome, this, &zErrMsg) != SQLITE_OK)
		printf("SQL error: %s\n", zErrMsg);
}



/***********************************************************************
     * Container
     * loadBiome

***********************************************************************/
int fired::Container::loadBiome(void *data, int, char **argv, char **) {
	((fired::Container *) data)->biomes.push_back(new fired::Biome(argv[6]));
	fired::Biome *current = ((fired::Container *) data)->biomes.back();

	sscanf(argv[2], "%hhu,%hhu,%hhu,%hhu", &current->skyHi.r     , &current->skyHi.g     , &current->skyHi.b     , &current->skyHi.a);
	sscanf(argv[3], "%hhu,%hhu,%hhu,%hhu", &current->skyLow.r    , &current->skyLow.g    , &current->skyLow.b    , &current->skyLow.a);
	sscanf(argv[5], "%hhu,%hhu,%hhu,%hhu", &current->lightness.r , &current->lightness.g , &current->lightness.b , &current->lightness.a);
	sscanf(argv[7], "%hhu,%hhu,%hhu,%hhu", &current->cloudColor.r, &current->cloudColor.g, &current->cloudColor.b, &current->cloudColor.a);

	strcpy(current->name   , argv[1]);
	strcpy(current->weather, argv[4]);

	current->ground      = ((fired::Container *) data)->tilesets[atoi(argv[8] ) - 1];
	current->brickMain   = ((fired::Container *) data)->tilesets[atoi(argv[9] ) - 1];
	current->brickSecond = ((fired::Container *) data)->tilesets[atoi(argv[10]) - 1];
	current->extra       = ((fired::Container *) data)->tilesets[atoi(argv[11]) - 1];

	return 0;
}



/***********************************************************************
     * Container
     * getBiome

***********************************************************************/
fired::Biome *fired::Container::getBiome(const char *name) {
	for (unsigned int i = 0; i < biomes.size(); i++)
		if (!strcmp(name, biomes[i]->name)) return biomes[i];

	return NULL;
}
