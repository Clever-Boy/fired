/***********************************************************************
     * File       : misc.hpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MISC
#define __MISC


sf::Color mixColors(sf::Color c1, sf::Color c2);
void swapItems(fired::InventoryItem *item1, fired::InventoryItem *item2);
void emptyItem(fired::InventoryItem *item);
float lessOrZero(float x);
float sqr(float x);
float sign(float x);
bool directoryContents(const char *dir, std::vector<std::string>* contents);
bool lineBoxCollision(sf::FloatRect box, sf::FloatRect ray, sf::Vector2f *coord, sf::Vector2f *normal, float *dist);

#endif
