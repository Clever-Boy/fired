/***********************************************************************
     * File       : weather_snow.hpp
     * Created    : Feb 14, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WEATHER_SNOW
#define __WEATHER_SNOW


namespace fired {
	struct WeatherSnow: Weather {
		WeatherSnow(fired::World *_world, float _frequency, float _wind);
	};
}

#endif

