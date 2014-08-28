/***********************************************************************
     * File       : misc_base.hpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MISC_BASE
#define __MISC_BASE


void swapItems(fired::InventoryItem *item1, fired::InventoryItem *item2);
void emptyItem(fired::InventoryItem *item);
void emptyStats(fired::CharacterStats *stats);
void createWindow();
void videoModeList(std::vector<std::string>* contents);
float lessOrZero(float x);
float sqr(float x);
float sign(float x);
float getRandomOffset(float offsetAmount);
bool directoryContents(const char *dir, std::vector<std::string>* contents);
bool printableChar(char c);
bool backspaceChar(char c);
bool lineBoxCollision(sf::FloatRect box, sf::FloatRect ray, sf::Vector2f *coord, sf::Vector2f *normal, float *dist);

#endif
