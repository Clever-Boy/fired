/***********************************************************************
     * File       : map_biome.cpp
     * Created    : Jan 22, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Biome
     * getWeather

***********************************************************************/
fired::Weather *fired::Biome::getWeather(fired::World *world) {
	char weather_type[32];
	float weather_intensity;

	sscanf(weather, "%[^,],%f", weather_type, &weather_intensity);

	if (!strcmp(weather_type, "rain" )) return new fired::WeatherRain (world, weather_intensity, rand() % 90 - 45);
	if (!strcmp(weather_type, "snow" )) return new fired::WeatherSnow (world, weather_intensity, rand() % 90 - 45);
	if (!strcmp(weather_type, "storm")) return new fired::WeatherStorm(world, weather_intensity, rand() % 90 - 45);

	return NULL;
}
