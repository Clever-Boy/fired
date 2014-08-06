/***********************************************************************
     * File       : misc_world_properties.hpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MISC_WORLD_PROPERTIES
#define __MISC_WORLD_PROPERTIES


namespace fired {
	struct WorldProperties {
		unsigned int creaturesLimit;
		unsigned int crittersLimit;
		unsigned int bossesLimit;

		float creaturesRate;
		float crittersRate;
		float bossesRate;
	};
}

#endif
