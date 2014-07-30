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

		sscanf(s, "%[^,],(%f,%f)\n", field, &bodypart->offset.x, &bodypart->offset.y);
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



/***********************************************************************
     * Container
     * loadModelColors

***********************************************************************/
void fired::Container::loadModelColors(const char *s, fired::BaseCreature *creature) {
	switch (creature->model->type) {
		case mtHumanoid: {
			creature->colors = new fired::ModelHumanoidColors;
			fired::ModelHumanoidColors *current = (fired::ModelHumanoidColors*)creature->colors;

			sscanf(strstr(s, "legsf"), "legsf=%hhu,%hhu,%hhu,%hhu\n", &current->partLegsF.r, &current->partLegsF.g, &current->partLegsF.b, &current->partLegsF.a);
			sscanf(strstr(s, "legsb"), "legsb=%hhu,%hhu,%hhu,%hhu\n", &current->partLegsB.r, &current->partLegsB.g, &current->partLegsB.b, &current->partLegsB.a);
			sscanf(strstr(s, "shoef"), "shoef=%hhu,%hhu,%hhu,%hhu\n", &current->partShoeF.r, &current->partShoeF.g, &current->partShoeF.b, &current->partShoeF.a);
			sscanf(strstr(s, "shoeb"), "shoeb=%hhu,%hhu,%hhu,%hhu\n", &current->partShoeB.r, &current->partShoeB.g, &current->partShoeB.b, &current->partShoeB.a);
			sscanf(strstr(s, "fistf"), "fistf=%hhu,%hhu,%hhu,%hhu\n", &current->partFistF.r, &current->partFistF.g, &current->partFistF.b, &current->partFistF.a);
			sscanf(strstr(s, "fistb"), "fistb=%hhu,%hhu,%hhu,%hhu\n", &current->partFistB.r, &current->partFistB.g, &current->partFistB.b, &current->partFistB.a);
			sscanf(strstr(s, "arms" ), "arms=%hhu,%hhu,%hhu,%hhu\n" , &current->partArms.r , &current->partArms.g , &current->partArms.b , &current->partArms.a );
			sscanf(strstr(s, "hair" ), "hair=%hhu,%hhu,%hhu,%hhu\n" , &current->partHair.r , &current->partHair.g , &current->partHair.b , &current->partHair.a );
			sscanf(strstr(s, "head" ), "head=%hhu,%hhu,%hhu,%hhu\n" , &current->partHead.r , &current->partHead.g , &current->partHead.b , &current->partHead.a );
			sscanf(strstr(s, "body" ), "body=%hhu,%hhu,%hhu,%hhu\n" , &current->partBody.r , &current->partBody.g , &current->partBody.b , &current->partBody.a );
		} break;


		case mtAnimal: {
			creature->colors = new fired::ModelAnimalColors;
			fired::ModelAnimalColors *current = (fired::ModelAnimalColors*)creature->colors;

			sscanf(strstr(s, "legsff"), "legsff=%hhu,%hhu,%hhu,%hhu\n", &current->partLegsFF.r, &current->partLegsFF.g, &current->partLegsFF.b, &current->partLegsFF.a);
			sscanf(strstr(s, "legsbf"), "legsbf=%hhu,%hhu,%hhu,%hhu\n", &current->partLegsBF.r, &current->partLegsBF.g, &current->partLegsBF.b, &current->partLegsBF.a);
			sscanf(strstr(s, "legsfb"), "legsfb=%hhu,%hhu,%hhu,%hhu\n", &current->partLegsFB.r, &current->partLegsFB.g, &current->partLegsFB.b, &current->partLegsFB.a);
			sscanf(strstr(s, "legsbb"), "legsbb=%hhu,%hhu,%hhu,%hhu\n", &current->partLegsBB.r, &current->partLegsBB.g, &current->partLegsBB.b, &current->partLegsBB.a);
			sscanf(strstr(s, "tail"  ), "tail=%hhu,%hhu,%hhu,%hhu\n"  , &current->partTail.r  , &current->partTail.g  , &current->partTail.b  , &current->partTail.a  );
			sscanf(strstr(s, "head"  ), "head=%hhu,%hhu,%hhu,%hhu\n"  , &current->partHead.r  , &current->partHead.g  , &current->partHead.b  , &current->partHead.a  );
			sscanf(strstr(s, "body"  ), "body=%hhu,%hhu,%hhu,%hhu\n"  , &current->partBody.r  , &current->partBody.g  , &current->partBody.b  , &current->partBody.a  );
		} break;
	}
}
