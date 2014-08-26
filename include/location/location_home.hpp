/***********************************************************************
     * File       : location_home.hpp
     * Created    : Aug 26, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __LOCATION_HOME
#define __LOCATION_HOME


namespace fired {
	struct LocationHome {
		fired::Map                   *map;
		fired::LocationHomeStructure  metadata;


		 LocationHome(fired::Camera *_cam, fired::World *_world);
		~LocationHome();
	};
}

#endif
