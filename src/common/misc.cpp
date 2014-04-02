/***********************************************************************
     * File       : misc.cpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * swapItems

***********************************************************************/
void swapItems(fired::InventoryItem *item1, fired::InventoryItem *item2) {
	fired::InventoryItem tmp;

	tmp.base = item1->base;
	tmp.count = item1->count;

	item1->base = item2->base;
	item1->count = item2->count;

	item2->base = tmp.base;
	item2->count = tmp.count;
}



/***********************************************************************
     * emptyItem

***********************************************************************/
void emptyItem(fired::InventoryItem *item) {
	item->base = NULL;
	item->count = 0;
}



/***********************************************************************
     * emptyStats

***********************************************************************/
void emptyStats(fired::CharacterStats *stats) {
	stats->accel    = 0.0f;
	stats->speed    = 0.0f;
	stats->aimrange = 0.0f;
	stats->jump     = 0.0f;
	stats->accuracy = 0.0f;
	stats->xpfactor = 0.0f;
	stats->armor    = 0;
	stats->maxHP    = 0;
}



/***********************************************************************
     * lessOrZero

***********************************************************************/
float lessOrZero(float x) {
	if (x > 0) return 0;
	else return x;
};



/***********************************************************************
     * sqr

***********************************************************************/
float sqr(float x) {
	return x * x;
}



/***********************************************************************
     * mixColors

***********************************************************************/
sf::Color mixColors(sf::Color c1, sf::Color c2) {
	sf::Color result;

	result.a = 255;
	result.r = (c1.r > c2.r) ? c1.r : c2.r;
	result.g = (c1.g > c2.g) ? c1.g : c2.g;
	result.b = (c1.b > c2.b) ? c1.b : c2.b;

	return result;
}



/***********************************************************************
     * canMixColors

***********************************************************************/
bool canMixColors(sf::Color base, sf::Color light) {
	if (light.r > base.r) return true;
	if (light.g > base.g) return true;
	if (light.b > base.b) return true;

	return false;
}



/***********************************************************************
     * sign

***********************************************************************/
float sign(float x) {
	if (x > 0) return 1.0f;
	if (x < 0) return -1.0f;
	return 0.0f;
}



/***********************************************************************
     * getRandomOffset

***********************************************************************/
float getRandomOffset(float offsetAmount) {
	return float(random() % 400 - 200) * offsetAmount / 200.0;
}



/***********************************************************************
                       Fast Ray-Box Intersection
                           by Andrew Woo
              from "Graphics Gems", Academic Press, 1990
***********************************************************************/
bool lineBoxCollision(sf::FloatRect box, sf::FloatRect ray, sf::Vector2f *coord, sf::Vector2f *normal, float *dist)
{
	bool inside = true;
	sf::Vector2i quadrant;
	int whichPlane;
	sf::Vector2f maxT;
	sf::Vector2f candidatePlane;


	if(ray.left < box.left) {
		quadrant.x = LEFT;
		candidatePlane.x = box.left;
		inside = false;
	} else if (ray.left > box.left + box.width) {
		quadrant.x = RIGHT;
		candidatePlane.x = box.left + box.width;
		inside = false;
	} else {
		quadrant.x = MIDDLE;
	}

	if(ray.top < box.top) {
		quadrant.y = LEFT;
		candidatePlane.y = box.top;
		inside = false;
	} else if (ray.top > box.top + box.height) {
		quadrant.y = RIGHT;
		candidatePlane.y = box.top + box.height;
		inside = false;
	} else {
		quadrant.y = MIDDLE;
	}


	if(inside)	{
		*coord = sf::Vector2f(ray.left, ray.top);
		return true;
	}


	if (quadrant.x != MIDDLE && ray.width !=0.)
		maxT.x = (candidatePlane.x - ray.left) / ray.width;
	else
		maxT.x = -1.;

	if (quadrant.y != MIDDLE && ray.height !=0.)
		maxT.y = (candidatePlane.y - ray.top) / ray.height;
	else
		maxT.y = -1.;


	whichPlane = 0;
	if (maxT.x < maxT.y)
		whichPlane = 1;


	if (whichPlane == 0) {
		if (maxT.x < 0.) return false;
	} else {
		if (maxT.y < 0.) return false;
	}

	if (whichPlane == 0) {
		coord->x = candidatePlane.x;
		coord->y = ray.top + maxT.x * ray.height;

		normal->x = quadrant.x;
		normal->y = 0;

		if (coord->y < box.top || coord->y > (box.top + box.height)) return false;
	} else {
		coord->x = ray.left + maxT.y * ray.width;
		coord->y = candidatePlane.y;

		normal->x = 0;
		normal->y = quadrant.y;

		if (coord->x < box.left || coord->x > (box.left + box.width)) return false;
	}

	if (dist) {
		 *dist = vLen(sf::Vector2f(coord->x - ray.left, coord->y - ray.top));
		 if (*dist > vLen(sf::Vector2f(ray.width, ray.height))) return false;
	}
	return true;
}
