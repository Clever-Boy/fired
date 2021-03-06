/***********************************************************************
     * File       : container_settings.hpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CONTAINER_SETTINGS
#define __CONTAINER_SETTINGS


namespace fired {
	struct Settings {
		struct {
			unsigned int width;
			unsigned int height;
			unsigned int bpp;
			unsigned int antialiasing;
			bool fullScreen;
		} window;

		struct {
			int music;
			int sound;
		} volume;


		 Settings();
		~Settings();

		void save();
		void loadFromFile(const char *filename);
		void saveToFile(const char *filename);
	};
}

#endif
