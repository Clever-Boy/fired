/***********************************************************************
     * File       : lighting.hpp
     * Created    : Feb 04, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __LIGHTING
#define __LIGHTING


void light();
void resetLight();
void buildLight();
void renderLight();
void setIntensity(fired::Tile *tile, char intensity);
void checkNeighbours(fired::Tile *tile);
void addLightSource(int x, int y, char intensity);
sf::Uint8    getColor(char intensity);
sf::Vector2f getTilePos(int x, int y);
sf::Color    getTileLight(int x, int y);

#endif
