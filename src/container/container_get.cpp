/***********************************************************************
     * File       : container_get.cpp
     * Created    : May 05, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Container
     * getAI

***********************************************************************/
fired::BaseAI *fired::Container::getAI(const char *name, fired::Creature *owner, fired::World *world) {
	if (!strcmp(name, "idle")) return new fired::IdleAI(owner, world);
	if (!strcmp(name, "basic")) return new fired::BasicAI(owner, world);
	if (!strcmp(name, "critter")) return new fired::CritterAI(owner, world);

	return new fired::BaseAI(owner, world);
}



/***********************************************************************
     * Container
     * getSound

***********************************************************************/
fired::GameSound* fired::Container::getSound(const char *name) {
	for (unsigned int i = 0; i < sounds.size(); i++)
		if (!strcmp(name, sounds[i]->name)) return sounds[i];

	return NULL;
}



/***********************************************************************
     * Container
     * getDecor

***********************************************************************/
unsigned int fired::Container::getDecor(const char *name) {
	for (unsigned int i = 0; i < decors.size(); i++)
		if (!strcmp(name, decors[i]->name)) return i;

	return -1;
}



/***********************************************************************
     * Container
     * getLight

***********************************************************************/
unsigned int fired::Container::getLight(const char *name) {
	for (unsigned int i = 0; i < lights.size(); i++)
		if (!strcmp(name, lights[i]->name)) return i;

	return -1;
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
     * getArmorIndex

***********************************************************************/
unsigned int fired::Container::getArmorIndex(const char *name) {
	for (unsigned int i = 0; i < armors.size(); i++)
		if (!strcmp(name, armors[i]->name)) return i;

	return -1;
}



/***********************************************************************
     * Container
     * getWeaponIndex

***********************************************************************/
unsigned int fired::Container::getWeaponIndex(const char *name) {
	for (unsigned int i = 0; i < weapons.size(); i++)
		if (!strcmp(name, weapons[i]->name)) return i;

	return -1;
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
     * getItemIndex

***********************************************************************/
unsigned int fired::Container::getItemIndex(const char *name) {
	for (unsigned int i = 0; i < items.size(); i++)
		if (!strcmp(name, items[i]->name)) return i;

	return -1;
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
     * getTileset

***********************************************************************/
unsigned int fired::Container::getTileset(const char *name) {
	for (unsigned int i = 0; i < tilesets.size(); i++)
		if (!strcmp(name, tilesets[i]->name)) return tilesets[i]->ID;

	return -1;
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



/***********************************************************************
     * Container
     * getExplosion

***********************************************************************/
fired::BaseExplosion *fired::Container::getExplosion() {
	if (explosions.size() == 0) return 0;
	else return explosions[rand() % explosions.size()];
}



/***********************************************************************
     * Container
     * getAmmoIndex

***********************************************************************/
unsigned int fired::Container::getAmmoIndex(const char *name) {
	for (unsigned int i = 0; i < weapons.size(); i++)
		if (!strcmp(name, ammos[i]->name)) return i;

	return -1;
}
