/***********************************************************************
     * File       : container_load.hpp
     * Created    : May 05, 2015
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CONTAINER_LOAD
#define __CONTAINER_LOAD


static int loadSprite   (void *data, int argc, char **argv, char **azColName);
static int loadSound    (void *data, int argc, char **argv, char **azColName);
static int loadDecor    (void *data, int argc, char **argv, char **azColName);
static int loadLight    (void *data, int argc, char **argv, char **azColName);
static int loadBodypart (void *data, int argc, char **argv, char **azColName);
static int loadModel    (void *data, int argc, char **argv, char **azColName);
static int loadArmor    (void *data, int argc, char **argv, char **azColName);
static int loadWeapon   (void *data, int argc, char **argv, char **azColName);
static int loadAmmo     (void *data, int argc, char **argv, char **azColName);
static int loadItem     (void *data, int argc, char **argv, char **azColName);
static int loadCreature (void *data, int argc, char **argv, char **azColName);
static int loadTileset  (void *data, int argc, char **argv, char **azColName);
static int loadBiome    (void *data, int argc, char **argv, char **azColName);
static int loadExplosion(void *data, int argc, char **argv, char **azColName);

#endif
