/***********************************************************************
     * File       : container_base.hpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CONTAINER_BASE
#define __CONTAINER_BASE


#include <sqlite3.h>


namespace fired {
	struct Container {
		std::vector<fired::BaseWeapon*>      weapons;
		std::vector<fired::BaseArmor*>       armors;
		std::vector<fired::BaseAmmo*>        ammos;
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

		fired::LoadingScr *screen;


		 Container(fired::LoadingScr *_screen);
		~Container();

		#include "container_misc.hpp"
		#include "container_get.hpp"
		#include "container_load.hpp"
	};
}

#endif
