/***********************************************************************
     * File       : misc_light.hpp
     * Created    : Aug 19, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MISC_LIGHT
#define __MISC_LIGHT


sf::Color mixColors(sf::Color c1, sf::Color c2);
sf::Color applyIntensity(sf::Color c, char intensity);
sf::Color reapplyIntensity(sf::Color c, char intensity1, char intensity2);
bool canMixColors(sf::Color base, sf::Color light);

#endif
