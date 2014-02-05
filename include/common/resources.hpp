/***********************************************************************
     * File       : resources.hpp
     * Created    : Feb 05, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __RESOURCES
#define __RESOURCES


namespace fired {
	struct Resources {
		struct {
			sf::SoundBuffer *explosion_buf;

			sf::Sound       *explosion;
		} sounds;


		 Resources();
		~Resources();
	};
}

#endif
