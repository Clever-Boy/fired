/***********************************************************************
     * File       : container_get.hpp
     * Created    : May 05, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CONTAINER_GET
#define __CONTAINER_GET


sf::Sound            *getSound(const char *name);
fired::BaseAI        *getAI(const char *name, fired::Creature *owner, fired::World *world);
fired::BaseItem      *getItem(const char *name);
fired::BaseCreature  *getCreature(const char *name);
fired::Biome         *getBiome(const char *name);
fired::BaseExplosion *getExplosion();
fired::BaseBodypart  *getBodypart(const char* name, fired::BodypartType type);
unsigned int          getDecor(const char* name);
unsigned int          getLight(const char* name);
unsigned int          getArmorIndex(const char *name);
unsigned int          getWeaponIndex(const char *name);
unsigned int          getAmmoIndex(const char *name);
unsigned int          getItemIndex(const char *name);
unsigned int          getTileset(const char *name);

#endif
