/***********************************************************************
     * File       : gen_biome_city.hpp
     * Created    : Apr 02, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __GEN_BIOME_CITY
#define __GEN_BIOME_CITY


struct {
	std::vector<fired::MapLootItem*> simpleLoot;
	std::vector<fired::MapLootItem*> bigLoot;
} city;


void genCity();
void genCityMeta();
void genCityPalette();
void genCityCreateLoot();
void genCityClearLoot();
void genCityLandscape();
void genCityPlayer();
void genCitySpawns();
void genCityDecors();
void genCityPlatforms();
void genCityCollectors();

#endif
