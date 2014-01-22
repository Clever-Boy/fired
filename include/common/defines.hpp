/***********************************************************************
     * File       : defines.hpp
     * Created    : Aug 23, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __DEFINES
#define __DEFINES

#define PROJECT_CAPTION         "F.I.R.E.D."
#define PROJECT_VER             "0.99"
#define PROJECT_KEY             "the key"


#define deleteList(list) for (; !(list).empty(); delete (list)[(list).size() - 1], (list).pop_back())
#define updateList(list) for (unsigned int i = 0; i < (list).size();) { if (!(list)[i]->update()) {delete (list)[i]; (list).erase((list).begin() + i);} else i++;}


#define NUMDIM                  2
#define LEFT                   -1
#define MIDDLE                  0
#define RIGHT                   1


#define PHYS_GRAVITY            1500.0f
#define PHYS_MAX_FALL           2500.0f
#define PHYS_TUNNEL_TIME        8.0f
#define PHYS_TUNNEL_CHUNK       3.0f
#define PHYS_SAFE_FALL          900.0f
#define PHYS_FRICTION_ACCEL     800.0f
#define PHYS_EPSILON            3.0f


#define PLAYER_RESPAWN_TIME     3.0f
#define ITEM_SPEED              100.0f
#define ITEM_MAX_STACK          25
#define TILE_SIZE               16.0f
#define BROAD_ATTACK_TIME       0.25f


#define MENU_X_OFFSET           50
#define MENU_Y_OFFSET           150
#define MENU_Y_DIFF             75
#define MENU_BG_SPEED           100.0f


#define CHUNK_LIFETIME          15.0f
#define CHUNK_DISAPPEARTIME     12.5f


#define STARTSCR_TIME_DELAY     4.0f
#define STARTSCR_TIME_APPEAR    1.5f
#define STARTSCR_TIME_DISAPPEAR 2.5f


#define CREDITSSCR_SPEED        50
#define CREDITSSCR_WIDTH        700


#define WEAPON_TYPE_RANGED      1
#define WEAPON_TYPE_MELEE       2
#define WEAPON_TYPE_BROAD       3


#define FLYTEXT_LIFETIME        0.5f
#define FLYTEXT_OFFSET          20.0f


#define FIRED_FRACTION_PLAYER  1
#define FIRED_FRACTION_SOLDIER 2

#endif
