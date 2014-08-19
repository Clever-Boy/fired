/***********************************************************************
     * File       : misc_light.cpp
     * Created    : Aug 19, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



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
     * applyIntensity

***********************************************************************/
sf::Color applyIntensity(sf::Color c, char intensity) {
	float k;

	if (intensity >= LIGHT_ABSOLUTE) k = 1.0f;
	else                             k = (float)intensity / (float)LIGHT_ABSOLUTE;


	sf::Color result;
	result.r = (char)(c.r * k);
	result.g = (char)(c.g * k);
	result.b = (char)(c.b * k);
	result.a = 255;

	return result;
}



/***********************************************************************
     * reapplyIntensity

***********************************************************************/
sf::Color reapplyIntensity(sf::Color c, char intensityOld, char intensityNew) {
	float k1, k2;

	if (intensityNew >= LIGHT_ABSOLUTE) k1 = 1.0f;
	else                                k1 = (float)intensityNew / (float)LIGHT_ABSOLUTE;

	if (intensityOld >= LIGHT_ABSOLUTE) k2 = 1.0f;
	else                                k2 = (float)intensityOld / (float)LIGHT_ABSOLUTE;


	sf::Color result;
	result.r = (char)(c.r * k1 / k2);
	result.g = (char)(c.g * k1 / k2);
	result.b = (char)(c.b * k1 / k2);
	result.a = 255;

	return result;
}
