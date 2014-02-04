/***********************************************************************
     * File       : physics.hpp
     * Created    : Feb 04, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __PHYSICS
#define __PHYSICS


bool isSolid(int i, int j);
bool isPlatform(int i, int j, fired::Phys *phys);

void checkCollision(fired::Phys *phys, fired::Character *character, int tile_x, int tile_y);
void checkPhys(fired::Phys *phys, fired::Character *character, float tunnelTime);
bool checkShot(fired::Shot *shot);

#endif
