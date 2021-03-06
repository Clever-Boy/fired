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
#define PROJECT_CAPTION          "F.I.R.E.D."
#define PROJECT_VER              "0.99 alpha"
#define PROJECT_KEY              "\x07\x03\x19\x88\xF1\x4E\xD0\x43\x20\x32\x98\xE2\x12"



/***********************************************************************
     * List processing macros

***********************************************************************/
#define deleteList(list)      for (; !(list).empty(); delete (list).back(), (list).pop_back())
#define updateList(list)      for (unsigned int i = 0; i < (list).size();) { if (!(list)[i]->update()) {delete (list)[i]; (list).erase((list).begin() + i);} else i++;}
#define updateCreatures(list) for (unsigned int i = 0; i < (list).size();) { (list)[i]->update(); if ((list)[i]->character->dead) {for (unsigned int j = 0; j < chars.size(); j++) if (chars[j] == (list)[i]->character) {chars.erase(chars.begin() + j); break;} delete (list)[i]; (list).erase((list).begin() + i);} else i++;}



/***********************************************************************
     * Architecture

***********************************************************************/
#if defined(__MINGW32__)
#	define MKDIR(dir) mkdir((dir))
#elif defined(_MSC_VER)
#	include <direct.h>
#	pragma warning(disable : 4996)
#	pragma warning(disable : 4703)
#	define MKDIR(dir) _mkdir((dir))
#else
#	define MKDIR(dir) mkdir((dir), 0755)
#endif



/***********************************************************************
     * Ray-cast constants

***********************************************************************/
#define NUMDIM                   2
#define LEFT                    -1
#define MIDDLE                   0
#define RIGHT                    1



/***********************************************************************
     * Math constants

***********************************************************************/
#define DEG_TO_RAD               0.01745f
#define RAD_TO_DEG               57.29578f



/***********************************************************************
     * Physics constants

***********************************************************************/
#define PHYS_GRAVITY             1500.0f
#define PHYS_MAX_FALL            2500.0f
#define PHYS_TUNNEL_TIME         8.0f
#define PHYS_TUNNEL_CHUNK        3.0f
#define PHYS_SAFE_FALL           900.0f
#define PHYS_FRICTION_ACCEL      1600.0f
#define PHYS_EPSILON             3.0f



/***********************************************************************
     * Player constants

***********************************************************************/
#define PLAYER_RESPAWN_TIME      3.0f
#define ITEM_SPEED               100.0f
#define TILE_SIZE                16.0f
#define BROAD_ATTACK_TIME        0.25f
#define MELEE_ATTACK_TIME        0.2f
#define WEAPON_SWITCH_COOLDOWN   0.5f



/***********************************************************************
     * Lighting constants

***********************************************************************/
#define LIGHT_OFFSCREEN_TILES    24
#define LIGHT_MAX_LIGHTLEVEL     100
#define LIGHT_ABSOLUTE           80

#define LIGHT_SPLASH_INTENSITY   100
#define LIGHT_SHOT_INTENSITY     45
#define LIGHT_SHOT_LIFETIME      0.5f



/***********************************************************************
     * Lighting constants

***********************************************************************/
#define LIGHTNING_OFFSET         96.0
#define LIGHTNING_LIFE           0.7
#define LIGHTNING_FADEOUT        0.4
#define LIGHTNING_ITERATIONS     5
#define LIGHTNING_MIN_TIME       2.0
#define LIGHTNING_MAX_TIME       6.0



/***********************************************************************
     * Main menu constants

***********************************************************************/
#define MENU_X_OFFSET            50
#define MENU_X_WINDOW_OFFSET     307
#define MENU_Y_OFFSET            150
#define MENU_Y_DIFF              75
#define MENU_BG_SPEED            100.0f



/***********************************************************************
     * Log constants

***********************************************************************/
#define LOG_SIZE                 6
#define LOG_MESSAGE_HEIGHT       12
#define LOG_MESSAGE_LIFE         7.5f
#define LOG_MESSAGE_FADING       1.5f
#define LOG_MESSAGE_SPEED        100.0f



/***********************************************************************
     * Chunk constants

***********************************************************************/
#define CHUNK_LIFETIME           15.0f
#define CHUNK_DISAPPEARTIME      12.5f



/***********************************************************************
     * Start screen constants

***********************************************************************/
#define STARTSCR_TIME_DELAY      4.0f
#define STARTSCR_TIME_APPEAR     1.5f
#define STARTSCR_TIME_DISAPPEAR  2.5f



/***********************************************************************
     * Credits screen constants

***********************************************************************/
#define CREDITSSCR_SPEED         50
#define CREDITSSCR_WIDTH         700



/***********************************************************************
     * Progress bar constants

***********************************************************************/
#define PROGRESSBAR_WIDTH        450
#define PROGRESSBAR_HEIGHT       16



/***********************************************************************
     * Weapon constants

***********************************************************************/
#define WEAPON_TYPE_RANGED       1
#define WEAPON_TYPE_MELEE        2
#define WEAPON_TYPE_BROAD        3

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
#define FLYTEXT_LIFETIME         0.5f
#define FLYTEXT_OFFSET           20.0f



/***********************************************************************
     * Fraction constants

***********************************************************************/
#define SOUND_MINDISTANCE        300.0f
#define SOUND_ATTENUATION        5.0f



/***********************************************************************
     * Skills constants

***********************************************************************/
#define SKILL_SPEED_K            1.0f
#define SKILL_ACCEL_K            2.0f
#define SKILL_JUMP_K             1.0f
#define SKILL_AIMRANGE_K         0.5f
#define SKILL_XPFACTOR_K         0.005f
#define SKILL_ACCURACY_K         1.5f
#define SKILL_ARMOR_K            1
#define SKILL_MAXHP_K            1



/***********************************************************************
     * Fraction constants

***********************************************************************/
#define FIRED_FRACTION_PLAYER    1
#define FIRED_FRACTION_SOLDIER   2
#define FIRED_FRACTION_CRITTER   3



/***********************************************************************
     * String constants

***********************************************************************/
#define INPUT_VALID_CHARS        "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM 1234567890-_=+[]^():;"



/***********************************************************************
     * MSVC snprintf

***********************************************************************/
#ifdef _MSC_VER
#define snprintf c99_snprintf

inline int c99_vsnprintf(char* str, size_t size, const char* format, va_list ap) {
	int count = -1;

	if (size != 0)
		count = _vsnprintf_s(str, size, _TRUNCATE, format, ap);
	if (count == -1)
		count = _vscprintf(format, ap);

	return count;
}

inline int c99_snprintf(char* str, size_t size, const char* format, ...) {
	int count;
	va_list ap;

	va_start(ap, format);
	count = c99_vsnprintf(str, size, format, ap);
	va_end(ap);

	return count;
}

#endif

#endif
