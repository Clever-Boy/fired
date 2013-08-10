#include "game.hpp"

//======================================================================


fired::Settings::Settings() {
	loadFromFile("data/settings.conf");
}

//======================================================================


void fired::Settings::save() {
	saveToFile("data/settings.conf");
}

//======================================================================


fired::Settings::~Settings() {
	save();
}

//======================================================================


void fired::Settings::loadFromFile(const char *filename) {
	FILE *fp = fopen(filename, "r");
	fscanf(fp, "window.width=%d\n"     , &window.width);
	fscanf(fp, "window.height=%d\n"    , &window.height);
	fscanf(fp, "window.bpp=%d\n"       , &window.bpp);
	fscanf(fp, "window.fullscreen=%d\n", (int *)&window.fullScreen);
	fscanf(fp, "volume.music=%d\n"     , &volume.music);
	fscanf(fp, "volume.sound=%d\n"     , &volume.sound);
	fclose(fp);
}

//======================================================================


void fired::Settings::saveToFile(const char *filename) {
	FILE *fp = fopen(filename, "w");
	fprintf(fp, "window.width=%d\n"     , window.width);
	fprintf(fp, "window.height=%d\n"    , window.height);
	fprintf(fp, "window.bpp=%d\n"       , window.bpp);
	fprintf(fp, "window.fullscreen=%d\n", window.fullScreen);
	fprintf(fp, "volume.music=%d\n"     , volume.music);
	fprintf(fp, "volume.sound=%d\n"     , volume.sound);
	fclose(fp);
}
