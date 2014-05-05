/***********************************************************************
     * File       : container_misc.cpp
     * Created    : May 05, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Container
     * loadContent

***********************************************************************/
void fired::Container::loadContent(sqlite3 *db, const char *table, int (*callback)(void*,int,char**,char**), const char *sql) {
	char *zErrMsg = 0;

	screen->mainBar->setCaption("Loading", table);
	screen->mainBar->increase();

	char countQuery[64];
	snprintf(countQuery, sizeof(countQuery), "SELECT COUNT(*) FROM %s", table);

	if (sqlite3_exec(db, countQuery, count   , this, &zErrMsg) != SQLITE_OK) printf("SQL error: %s\n", zErrMsg);
	if (sqlite3_exec(db, sql       , callback, this, &zErrMsg) != SQLITE_OK) printf("SQL error: %s\n", zErrMsg);
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
     * count

***********************************************************************/
int fired::Container::count(void *data, int, char **argv, char **) {
	((fired::Container *) data)->screen->secBar->reset();
	((fired::Container *) data)->screen->secBar->setLimit(atoi(argv[0]));

	return 0;
}



/***********************************************************************
     * Container
     * updateProgress

***********************************************************************/
void fired::Container::updateProgress(const char *caption) {
	screen->secBar->increase();
	screen->secBar->setCaption("Loading", caption);
	screen->render();
}
