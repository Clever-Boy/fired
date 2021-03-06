/***********************************************************************
     * File       : misc_vect.hpp
     * Created    : Sep 01, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MISC_VECT
#define __MISC_VECT


sf::Vector2f vNorm(sf::Vector2f v);
sf::Vector2f vSetLen(sf::Vector2f v, float l);
sf::Vector2f rectCenter(sf::FloatRect rect);
sf::Vector2f rectCenter(sf::IntRect rect);
float        vLen(sf::Vector2f v);

#endif
