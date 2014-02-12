/***********************************************************************
     * File       : particle_weather.hpp
     * Created    : Feb 12, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __PARTICLE_WEATHER
#define __PARTICLE_WEATHER


namespace fired {
	struct ParticleSystemWeather: ParticleSystemSpray {
		fired::Camera *cam;


		ParticleSystemWeather(fired::World *world);
	};
}

#endif

