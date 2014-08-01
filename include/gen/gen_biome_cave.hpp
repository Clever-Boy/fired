/***********************************************************************
     * File       : gen_biome_cave.hpp
     * Created    : Apr 02, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __GEN_BIOME_CAVE
#define __GEN_BIOME_CAVE


void genCave();
void genCaveMeta();
void genCavePalette();
void genCaveCreateLoot();
void genCaveClearLoot();
void genCaveLandscape(int areaStart, int areaEnd, int horizon);
void genCavePlayer();
void genCaveSpawns();
void genCaveDecors();
void genCavePlatforms();
void genCaveCollectors();

#endif
