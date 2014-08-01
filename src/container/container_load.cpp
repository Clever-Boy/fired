/***********************************************************************
     * File       : container_load.cpp
     * Created    : May 05, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Container
     * loadSprite

***********************************************************************/
int fired::Container::loadSprite(void *data, int, char **argv, char **) {
	((fired::Container *) data)->updateProgress(argv[0]);
	((fired::Container *) data)->sprites.push_back(new fired::GameSprite(argv[0]));

	return 0;
}



/***********************************************************************
     * Container
     * loadSound

***********************************************************************/
int fired::Container::loadSound(void *data, int, char **argv, char **) {
	((fired::Container *) data)->updateProgress(argv[1]);
	((fired::Container *) data)->sounds.push_back(new fired::GameSound(argv[1], argv[0]));

	return 0;
}



/***********************************************************************
     * Container
     * loadDecor

***********************************************************************/
int fired::Container::loadDecor(void *data, int, char **argv, char **) {
	((fired::Container *) data)->updateProgress(argv[1]);

	sf::Vector2f size;
	sscanf(argv[2], "%f,%f", &size.x, &size.y);
	((fired::Container *) data)->decors.push_back(new fired::BaseDecor(argv[1], size, ((fired::Container *) data)->sprites[atoi(argv[4])]));

	return 0;
}



/***********************************************************************
     * Container
     * loadLight

***********************************************************************/
int fired::Container::loadLight(void *data, int, char **argv, char **) {
	((fired::Container *) data)->updateProgress(argv[0]);
	((fired::Container *) data)->lights.push_back(new fired::BaseLightSource);
	fired::BaseLightSource *current = ((fired::Container *) data)->lights.back();

	strcpy(current->name, argv[0]);
	sscanf(argv[1], "%d,%d", &current->offset.x, &current->offset.y);
	sscanf(argv[4], "%hhu,%hhu,%hhu", &current->color.r, &current->color.g, &current->color.b);
	current->intensity = (char)atoi(argv[2]);
	current->decor     = ((fired::Container *) data)->decors[atoi(argv[3])];
	current->color.a   = 255;

	return 0;
}



/***********************************************************************
     * Container
     * loadBodypart

***********************************************************************/
int fired::Container::loadBodypart(void *data, int, char **argv, char **) {
	((fired::Container *) data)->updateProgress(argv[0]);
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
	if (!strcmp(argv[1], "misc"  )) current->type = bptMisc;
	if (!strcmp(argv[1], "weapon")) current->type = bptWeapon;

	sscanf(argv[2], "%f,%f", &current->origin.x, &current->origin.y);
	current->sprite = ((fired::Container *) data)->sprites[atoi(argv[3])]->spr;
	current->size   = sf::Vector2f(((fired::Container *) data)->sprites[atoi(argv[3])]->tex->getSize());
	return 0;
}



/***********************************************************************
     * Container
     * loadModel

***********************************************************************/
int fired::Container::loadModel(void *data, int, char **argv, char **) {
	((fired::Container *) data)->updateProgress(argv[2]);

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
		return 0;
	}


	if (!strcmp(argv[1], "animal")) {
		fired::BaseModelAnimal *model = new fired::BaseModelAnimal;
		model->type = mtAnimal;

		sscanf(argv[3], "%f,%f\n", &model->size.x, &model->size.y);
		sscanf(argv[4], "%f,%f\n", &model->weaponOffset.x, &model->weaponOffset.y);

		sscanf(strstr(argv[5], "legsff"), "legsff=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partLegsFF, bptLegs);
		sscanf(strstr(argv[5], "legsbf"), "legsbf=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partLegsBF, bptLegs);
		sscanf(strstr(argv[5], "legsfb"), "legsfb=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partLegsFB, bptLegs);
		sscanf(strstr(argv[5], "legsbb"), "legsbb=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partLegsBB, bptLegs);
		sscanf(strstr(argv[5], "tail"  ), "tail=%s\n"  , field); ((fired::Container *) data)->loadModelBodypart(field, &model->partTail  , bptMisc);
		sscanf(strstr(argv[5], "head"  ), "head=%s\n"  , field); ((fired::Container *) data)->loadModelBodypart(field, &model->partHead  , bptHead);
		sscanf(strstr(argv[5], "body"  ), "body=%s\n"  , field); ((fired::Container *) data)->loadModelBodypart(field, &model->partBody  , bptBody);

		((fired::Container *) data)->models.push_back(model);
		return 0;
	}


	if (!strcmp(argv[1], "spider")) {
		fired::BaseModelSpider *model = new fired::BaseModelSpider;
		model->type = mtSpider;

		sscanf(argv[3], "%f,%f\n", &model->size.x, &model->size.y);
		sscanf(argv[4], "%f,%f\n", &model->weaponOffset.x, &model->weaponOffset.y);

		sscanf(strstr(argv[5], "legsf1"), "legsf1=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partLegsF1, bptLegs);
		sscanf(strstr(argv[5], "legsf2"), "legsf2=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partLegsF2, bptLegs);
		sscanf(strstr(argv[5], "legsf3"), "legsf3=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partLegsF3, bptLegs);
		sscanf(strstr(argv[5], "legsf4"), "legsf4=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partLegsF4, bptLegs);
		sscanf(strstr(argv[5], "shoef1"), "shoef1=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partShoeF1, bptShoe);
		sscanf(strstr(argv[5], "shoef2"), "shoef2=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partShoeF2, bptShoe);
		sscanf(strstr(argv[5], "shoef3"), "shoef3=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partShoeF3, bptShoe);
		sscanf(strstr(argv[5], "shoef4"), "shoef4=%s\n", field); ((fired::Container *) data)->loadModelBodypart(field, &model->partShoeF4, bptShoe);
		sscanf(strstr(argv[5], "head"  ), "head=%s\n"  , field); ((fired::Container *) data)->loadModelBodypart(field, &model->partHead  , bptHead);
		sscanf(strstr(argv[5], "body"  ), "body=%s\n"  , field); ((fired::Container *) data)->loadModelBodypart(field, &model->partBody  , bptBody);

		((fired::Container *) data)->models.push_back(model);
		return 0;
	}

	return 0;
}



/***********************************************************************
     * Container
     * loadArmor

***********************************************************************/
int fired::Container::loadArmor(void *data, int, char **argv, char **) {
	((fired::Container *) data)->updateProgress(argv[1]);
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
     * loadWeapon

***********************************************************************/
int fired::Container::loadWeapon(void *data, int, char **argv, char **){
	((fired::Container *) data)->updateProgress(argv[2]);
	((fired::Container *) data)->weapons.push_back(new fired::BaseWeapon);
	fired::BaseWeapon *current = ((fired::Container *) data)->weapons.back();

	strcpy(current->name   , argv[1]);
	strcpy(current->caption, argv[2]);

	sscanf(argv[4], "%d", &current->damage);
	sscanf(argv[5], "%f", &current->range);
	sscanf(argv[6], "%f", &current->cooldown);
	sscanf(argv[7], "%f", &current->knockback);

	if (!strcmp(argv[9], "broad" )) current->type = WEAPON_TYPE_BROAD;
	if (!strcmp(argv[9], "melee" )) current->type = WEAPON_TYPE_MELEE;
	if (!strcmp(argv[9], "ranged")) current->type = WEAPON_TYPE_RANGED;


	if (!strcmp(argv[10], "broad"))     current->subtype = WEAPON_SUBTYPE_BROAD;
	if (!strcmp(argv[10], "melee"))     current->subtype = WEAPON_SUBTYPE_MELEE;
	if (!strcmp(argv[10], "pistol"))    current->subtype = WEAPON_SUBTYPE_PISTOL;
	if (!strcmp(argv[10], "shotgun"))   current->subtype = WEAPON_SUBTYPE_SHOTGUN;
	if (!strcmp(argv[10], "rifle"))     current->subtype = WEAPON_SUBTYPE_RIFLE;
	if (!strcmp(argv[10], "energy"))    current->subtype = WEAPON_SUBTYPE_ENERGY;
	if (!strcmp(argv[10], "explosive")) current->subtype = WEAPON_SUBTYPE_EXPLOSIVE;


	if (argv[12] && (strlen(argv[12]) > 0)) sscanf(argv[12], "%f", &current->speed);

	if (atoi(argv[8])) current->automatic = true;
	else               current->automatic = false;

	if (argv[11] && (strlen(argv[11]) > 0)) current->shotSound  = ((fired::Container *) data)->getSound(argv[11]);
	else                                    current->shotSound = NULL;

	if (argv[13] && (strlen(argv[13]) > 0)) current->bodypart   = ((fired::Container *) data)->bodyparts[atoi(argv[13])];
	else                                    current->bodypart = NULL;

	return 0;
}



/***********************************************************************
     * Container
     * loadItem

***********************************************************************/
int fired::Container::loadItem(void *data, int, char **argv, char **) {
	((fired::Container *) data)->updateProgress(argv[1]);
	((fired::Container *) data)->items.push_back(new fired::BaseItem);
	fired::BaseItem *current = ((fired::Container *) data)->items.back();

	current->ID = atoi(argv[0]);

	strcpy(current->name, argv[1]);
	if (argv[6]) strcpy(current->tip , argv[6]);
	current->sprite = ((fired::Container *) data)->sprites[atoi(argv[7])];

	if (argv[5]) current->maxStack = atoi(argv[5]);
	else         current->maxStack = 0;

	if (!strcmp(argv[3], "armor" )) current->type = itArmor;
	if (!strcmp(argv[3], "weapon")) current->type = itWeapon;
	if (!strcmp(argv[3], "ammo"  )) current->type = itAmmo;

	switch (current->type) {
		case itAny:
			break;

		case itArmor:
			current->UID = ((fired::Container *) data)->getArmorIndex(argv[4]);
			break;

		case itWeapon:
			current->UID = ((fired::Container *) data)->getWeaponIndex(argv[4]);
			break;

		case itAmmo:
			current->UID = ((fired::Container *) data)->getAmmoIndex(argv[4]);
			break;
	}

	return 0;
}



/***********************************************************************
     * Container
     * loadCreature

***********************************************************************/
int fired::Container::loadCreature(void *data, int, char **argv, char **) {
	((fired::Container *) data)->updateProgress(argv[1]);
	((fired::Container *) data)->creatures.push_back(new fired::BaseCreature);
	fired::BaseCreature *current = ((fired::Container *) data)->creatures.back();
	emptyStats(&current->stats);

	strcpy(current->name, argv[1]);
	strcpy(current->ai  , argv[2]);

	if (!strcmp(argv[3], "player"))  current->fraction = FIRED_FRACTION_PLAYER;
	if (!strcmp(argv[3], "soldier")) current->fraction = FIRED_FRACTION_SOLDIER;
	if (!strcmp(argv[3], "critter")) current->fraction = FIRED_FRACTION_CRITTER;

	sscanf(argv[5] , "%f", &current->modelScale);
	sscanf(argv[8] , "%d", &current->stats.armor);
	sscanf(argv[9] , "%f", &current->stats.speed);
	sscanf(argv[10], "%f", &current->stats.accel);
	sscanf(argv[11], "%f", &current->stats.jump);
	sscanf(argv[12], "%f", &current->stats.aimrange);
	sscanf(argv[13], "%d", &current->stats.maxHP);

	current->model  = ((fired::Container *) data)->models[atoi(argv[16])];
	current->weapon = ((fired::Container *) data)->weapons[atoi(argv[17])];

	((fired::Container *) data)->loadModelColors(argv[15], current);

	if (argv[18] && strlen(argv[18]))
		current->ammo = ((fired::Container *) data)->ammos[atoi(argv[18])];
	else
		current->ammo = NULL;

	if (argv[14]) {
		char *token = strtok(argv[14], "\n");

		while (token) {
			((fired::Container *) data)->loadCreatureLoot(current, token);
			token = strtok(NULL, "\n");
		}
	}

	return 0;
}



/***********************************************************************
     * Container
     * loadTileset

***********************************************************************/
int fired::Container::loadTileset(void *data, int, char **argv, char **) {
	((fired::Container *) data)->updateProgress(argv[3]);
	((fired::Container *) data)->tilesets.push_back(new fired::Tileset(atoi(argv[0]), ((fired::Container *) data)->sprites[atoi(argv[1])], atoi(argv[2]), argv[3]));
	return 0;
}



/***********************************************************************
     * Container
     * loadBiome

***********************************************************************/
int fired::Container::loadBiome(void *data, int, char **argv, char **) {
	((fired::Container *) data)->updateProgress(argv[1]);
	((fired::Container *) data)->biomes.push_back(new fired::Biome);
	fired::Biome *current = ((fired::Container *) data)->biomes.back();

	current->intensity = atoi(argv[6]);

	sscanf(argv[3], "%hhu,%hhu,%hhu,%hhu", &current->lightness.r , &current->lightness.g , &current->lightness.b , &current->lightness.a);
	strcpy(current->name      , argv[1]);
	strcpy(current->background, argv[4]);

	if (argv[2]) strcpy(current->weather, argv[2]);
	else         current->weather[0] = 0;

	if (argv[5]) {
		char *token = strtok(argv[5], "\n");
		while (token) {
			current->creatures.push_back(((fired::Container *) data)->getCreature(token));
			token = strtok(NULL, "\n");
		}
	}

	return 0;
}



/***********************************************************************
     * Container
     * loadExplosion

***********************************************************************/
int fired::Container::loadExplosion(void *data, int, char **argv, char **) {
	((fired::Container *) data)->updateProgress(argv[1]);
	((fired::Container *) data)->explosions.push_back(new fired::BaseExplosion(argv[1]));
	return 0;
}



/***********************************************************************
     * Container
     * loadAmmo

***********************************************************************/
int fired::Container::loadAmmo(void *data, int, char **argv, char **){
	((fired::Container *) data)->updateProgress(argv[3]);
	((fired::Container *) data)->ammos.push_back(new fired::BaseAmmo);
	fired::BaseAmmo *current = ((fired::Container *) data)->ammos.back();

	strcpy(current->name   , argv[1]);
	strcpy(current->caption, argv[3]);

	sscanf(argv[4], "%d", &current->damage);

	if (!strcmp(argv[2], "broad"))     current->subtype = WEAPON_SUBTYPE_BROAD;
	if (!strcmp(argv[2], "melee"))     current->subtype = WEAPON_SUBTYPE_MELEE;
	if (!strcmp(argv[2], "pistol"))    current->subtype = WEAPON_SUBTYPE_PISTOL;
	if (!strcmp(argv[2], "shotgun"))   current->subtype = WEAPON_SUBTYPE_SHOTGUN;
	if (!strcmp(argv[2], "rifle"))     current->subtype = WEAPON_SUBTYPE_RIFLE;
	if (!strcmp(argv[2], "energy"))    current->subtype = WEAPON_SUBTYPE_ENERGY;
	if (!strcmp(argv[2], "explosive")) current->subtype = WEAPON_SUBTYPE_EXPLOSIVE;


	if (argv[6] && (strlen(argv[6]) > 0)) {
		sscanf(argv[6], "%f", &current->explosionRadius);
		current->explosive = true;
	} else {
		current->explosionRadius = 0.0f;
		current->explosive       = false;
	}


	current->tracer = stNone;
	if (argv[7] && (strlen(argv[7]) > 0)) {
		if (!strcmp(argv[7], "smoke")) current->tracer = stSmoke;
	}

	if (argv[8] && (strlen(argv[8]) > 0)) current->shotSprite = ((fired::Container *) data)->sprites[atoi(argv[8])];
	else                                  current->shotSprite = NULL;

	return 0;
}
