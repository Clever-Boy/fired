/***********************************************************************
     * File       : weather_storm.hpp
     * Created    : Feb 14, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WEATHER_STORM
#define __WEATHER_STORM

#include "weather_lightning.hpp"


namespace fired {
	struct WeatherStorm: Weather {
		fired::Lightning *lightning;


		 WeatherStorm(fired::World *_world, float _frequency, float _wind);
		~WeatherStorm();

		void update();
	};
}

#endif

