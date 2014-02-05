/***********************************************************************
     * File       : map_lighting.hpp
     * Created    : Feb 04, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MAP_LIGHTING
#define __MAP_LIGHTING


void light();
void resetLight();
void buildLight();
void renderLight();
void setIntensity(fired::Tile *tile, char intensity, sf::Color color);
void addIntensity(sf::Vector2i index, char intensity, sf::Color color);
void initIntensity(fired::Tile *tile, char intensity, sf::Color color);
void checkNeighbours(fired::Tile *tile);
void addTemporaryLightSource(sf::Vector2f pos, char intensity, sf::Color color, float lifetime);
void addExplosion(sf::Vector2f pos, float radius, float lifetime);
sf::Uint8    getColor(char intensity);
sf::Vector2f getTilePos(int x, int y);
sf::Color    getTileLight(int x, int y);

#endif
