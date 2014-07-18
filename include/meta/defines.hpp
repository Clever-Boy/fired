/***********************************************************************
     * File       : defines.hpp
     * Created    : Aug 23, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __DEFINES
#define __DEFINES



/***********************************************************************
     * Main project constants

***********************************************************************/
#define PROJECT_CAPTION         "F.I.R.E.D."
#define PROJECT_VER             "0.99 pre-alpha"
#define PROJECT_KEY             "the key"



/***********************************************************************
     * List processing macros

***********************************************************************/
#define deleteList(list) for (; !(list).empty(); delete (list).back(), (list).pop_back())
#define updateList(list) for (unsigned int i = 0; i < (list).size();) { if (!(list)[i]->update()) {delete (list)[i]; (list).erase((list).begin() + i);} else i++;}



/***********************************************************************
     * Architecture

***********************************************************************/
#ifdef __MINGW32__
#	define MKDIR(dir) mkdir((dir))
#else
#	define MKDIR(dir) mkdir((dir), 0755)
#endif



/***********************************************************************
     * Ray-cast constants

***********************************************************************/
#define NUMDIM                  2
#define LEFT                   -1
#define MIDDLE                  0
#define RIGHT                   1



/***********************************************************************
     * Physics constants

***********************************************************************/
#define PHYS_GRAVITY            1500.0f
#define PHYS_MAX_FALL           2500.0f
#define PHYS_TUNNEL_TIME        8.0f
#define PHYS_TUNNEL_CHUNK       3.0f
#define PHYS_SAFE_FALL          900.0f
#define PHYS_FRICTION_ACCEL     1600.0f
#define PHYS_EPSILON            3.0f



/***********************************************************************
     * Player constants

***********************************************************************/
#define PLAYER_RESPAWN_TIME     3.0f
#define ITEM_SPEED              100.0f
#define TILE_SIZE               16.0f
#define BROAD_ATTACK_TIME       0.25f
#define WEAPON_SWITCH_COOLDOWN  0.5f



/***********************************************************************
     * Lighting constants

***********************************************************************/
#define LIGHT_OFFSCREEN_TILES   24
#define LIGHT_MAX_LIGHTLEVEL    24
#define LIGHT_ABSOLUTE          20

#define LIGHT_SPLASH_INTENSITY  24
#define LIGHT_SHOT_INTENSITY    10
#define LIGHT_SHOT_LIFETIME     0.5f



/***********************************************************************
     * Lighting constants

***********************************************************************/
#define LIGHTNING_OFFSET     96.0
#define LIGHTNING_LIFE       0.7
#define LIGHTNING_FADEOUT    0.4
#define LIGHTNING_ITERATIONS 5
#define LIGHTNING_MIN_TIME   2.0
#define LIGHTNING_MAX_TIME   6.0



/***********************************************************************
     * Main menu constants

***********************************************************************/
#define MENU_X_OFFSET           50
#define MENU_Y_OFFSET           150
#define MENU_Y_DIFF             75
#define MENU_BG_SPEED           100.0f



/***********************************************************************
     * Chunk constants

***********************************************************************/
#define CHUNK_LIFETIME          15.0f
#define CHUNK_DISAPPEARTIME     12.5f



/***********************************************************************
     * Start screen constants

***********************************************************************/
#define STARTSCR_TIME_DELAY     4.0f
#define STARTSCR_TIME_APPEAR    1.5f
#define STARTSCR_TIME_DISAPPEAR 2.5f



/***********************************************************************
     * Credits screen constants

***********************************************************************/
#define CREDITSSCR_SPEED        50
#define CREDITSSCR_WIDTH        700



/***********************************************************************
     * Progress bar constants

***********************************************************************/
#define PROGRESSBAR_WIDTH        450
#define PROGRESSBAR_HEIGHT       16



/***********************************************************************
     * Weapon constants

***********************************************************************/
#define WEAPON_TYPE_RANGED      1
#define WEAPON_TYPE_MELEE       2
#define WEAPON_TYPE_BROAD       3

#define WEAPON_SUBTYPE_BROAD     0
#define WEAPON_SUBTYPE_MELEE     1
#define WEAPON_SUBTYPE_RIFLE     2
#define WEAPON_SUBTYPE_EXPLOSIVE 3
#define WEAPON_SUBTYPE_ENERGY    4
#define WEAPON_SUBTYPE_SHOTGUN   5
#define WEAPON_SUBTYPE_PISTOL    6

#define WEAPON_ZERO_ACCURACY     0.228f
#define WEAPON_SHOTGUN_OFFSET    0.188f
#define WEAPON_SHOTGUN_BULLETS   5


/***********************************************************************
     * FlyText constants

***********************************************************************/
#define FLYTEXT_LIFETIME        0.5f
#define FLYTEXT_OFFSET          20.0f



/***********************************************************************
     * Fraction constants

***********************************************************************/
#define SOUND_MINDISTANCE   300.0f
#define SOUND_ATTENUATION     5.0f



/***********************************************************************
     * Skills constants

***********************************************************************/
#define SKILL_SPEED_K     1.0f
#define SKILL_ACCEL_K     2.0f
#define SKILL_JUMP_K      1.0f
#define SKILL_AIMRANGE_K  0.5f
#define SKILL_XPFACTOR_K  0.005f
#define SKILL_ACCURACY_K  1.5f
#define SKILL_ARMOR_K     1
#define SKILL_MAXHP_K     1



/***********************************************************************
     * Fraction constants

***********************************************************************/
#define FIRED_FRACTION_PLAYER  1
#define FIRED_FRACTION_SOLDIER 2

#endif
