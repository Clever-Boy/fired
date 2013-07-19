#include "settings.hpp"

void fired::Settings::init() {
	loadFromFile("data/settings.conf");
}


void fired::Settings::save() {
	saveToFile("data/settings.conf");
}


void fired::Settings::loadFromFile(const char *filename) {
	return;
}


void fired::Settings::saveToFile(const char *filename) {
	return;
}
