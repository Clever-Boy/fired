/***********************************************************************
     * File       : weather_storm.hpp
     * Created    : Feb 14, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WEATHER_STORM
#define __WEATHER_STORM


namespace fired {
	struct WeatherStorm: Weather {
		WeatherStorm(fired::World *_world, float _frequency, float _wind);
	};
}

#endif

