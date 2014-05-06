/***********************************************************************
     * File       : container_settings.cpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Settings
     * constructor

***********************************************************************/
fired::Settings::Settings() {
	loadFromFile("data/settings.conf");
}



/***********************************************************************
     * Settings
     * destructor

***********************************************************************/
fired::Settings::~Settings() {
	save();
}



/***********************************************************************
     * Settings
     * save

***********************************************************************/
void fired::Settings::save() {
	saveToFile("data/settings.conf");
}



/***********************************************************************
     * Settings
     * loadFromFile

***********************************************************************/
void fired::Settings::loadFromFile(const char *filename) {
	FILE *fp = fopen(filename, "r");
	fscanf(fp, "window.width=%u\n"       , &window.width);
	fscanf(fp, "window.height=%u\n"      , &window.height);
	fscanf(fp, "window.fullscreen=%d\n"  , (int *)&window.fullScreen);
	fscanf(fp, "window.bpp=%u\n"         , &window.bpp);
	fscanf(fp, "window.antialiasing=%u\n", &window.antialiasing);
	fscanf(fp, "volume.music=%d\n"       , &volume.music);
	fscanf(fp, "volume.sound=%d\n"       , &volume.sound);
	fclose(fp);
}



/***********************************************************************
     * Settings
     * saveToFile

***********************************************************************/
void fired::Settings::saveToFile(const char *filename) {
	FILE *fp = fopen(filename, "w");
	fprintf(fp, "window.width=%u\n"       , window.width);
	fprintf(fp, "window.height=%u\n"      , window.height);
	fprintf(fp, "window.fullscreen=%hhu\n", window.fullScreen);
	fprintf(fp, "window.bpp=%u\n"         , window.bpp);
	fprintf(fp, "window.antialiasing=%u\n", window.antialiasing);
	fprintf(fp, "volume.music=%d\n"       , volume.music);
	fprintf(fp, "volume.sound=%d\n"       , volume.sound);
	fclose(fp);
}
