/***********************************************************************
     * File       : weather_rain.hpp
     * Created    : Feb 14, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WEATHER_RAIN
#define __WEATHER_RAIN


namespace fired {
	struct WeatherRain: Weather {
		 WeatherRain(fired::World *_world, float _frequency, float _wind);
		~WeatherRain();
	};
}

#endif

