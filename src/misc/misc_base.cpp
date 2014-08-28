/***********************************************************************
     * File       : misc_base.cpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * swapItems

***********************************************************************/
void swapItems(fired::InventoryItem *item1, fired::InventoryItem *item2) {
	fired::InventoryItem tmp;

	tmp.base = item1->base;
	tmp.count = item1->count;

	item1->base = item2->base;
	item1->count = item2->count;

	item2->base = tmp.base;
	item2->count = tmp.count;
}



/***********************************************************************
     * emptyItem

***********************************************************************/
void emptyItem(fired::InventoryItem *item) {
	item->base = NULL;
	item->count = 0;
}



/***********************************************************************
     * emptyStats

***********************************************************************/
void emptyStats(fired::CharacterStats *stats) {
	stats->accel    = 0.0f;
	stats->speed    = 0.0f;
	stats->aimrange = 0.0f;
	stats->jump     = 0.0f;
	stats->accuracy = 0.0f;
	stats->xpfactor = 0.0f;
	stats->armor    = 0;
	stats->maxHP    = 0;
}



/***********************************************************************
     * lessOrZero

***********************************************************************/
float lessOrZero(float x) {
	if (x > 0) return 0;
	else return x;
};



/***********************************************************************
     * sqr

***********************************************************************/
float sqr(float x) {
	return x * x;
}



/***********************************************************************
     * sign

***********************************************************************/
float sign(float x) {
	if (x > 0) return 1.0f;
	if (x < 0) return -1.0f;
	return 0.0f;
}



/***********************************************************************
     * getRandomOffset

***********************************************************************/
float getRandomOffset(float offsetAmount) {
	return float(rand() % 400 - 200) * offsetAmount / 200.0;
}



/***********************************************************************
     * printableChar

***********************************************************************/
bool printableChar(char c) {
	if (strchr(INPUT_VALID_CHARS, c)) return true;
	else                              return false;
}



/***********************************************************************
     * backspaceChar

***********************************************************************/
bool backspaceChar(char c) {
	return (c == '\b');
}



/***********************************************************************
     * directoryContents

***********************************************************************/
bool directoryContents(const char *dir, std::vector<std::string>* contents) {
	contents->clear();
	DIR *dir_ptr = opendir(dir);
	if (!dir_ptr) return false;

	dirent *dr;
	while ((dr = readdir(dir_ptr)))
		if (strcmp(dr->d_name, ".") && strcmp(dr->d_name, "..") && dr->d_name[0] != '.') 
			contents->push_back(dr->d_name);

	closedir(dir_ptr);
	return true;
}



/***********************************************************************
     * videoModeList

***********************************************************************/
void videoModeList(std::vector<std::string>* contents) {
	char mode[64];
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

	contents->clear();

	for (unsigned int i = 0; i < modes.size(); i++) {
		if (modes[i].width        < 800 ) continue;
		if (modes[i].width        > 1280) continue;
		if (modes[i].bitsPerPixel < 24  ) continue;
		if (modes[i].bitsPerPixel > 32  ) continue;

		snprintf(mode, sizeof(mode), "%d x %d x %dbpp", modes[i].width, modes[i].height, modes[i].bitsPerPixel);
		contents->push_back(mode);
	}
}



/***********************************************************************
     * getRandomOffset

***********************************************************************/
void createWindow() {
	unsigned long style;
	if (settings->window.fullScreen) style = sf::Style::Fullscreen;
	else                             style = sf::Style::Close;

	sf::ContextSettings contextSettings;
	contextSettings.antialiasingLevel = settings->window.antialiasing;

	app = new sf::RenderWindow(sf::VideoMode(settings->window.width,
	                           settings->window.height,
	                           settings->window.bpp),
	                           PROJECT_CAPTION " v" PROJECT_VER,
	                           style,
	                           contextSettings);
	app->setMouseCursorVisible(false);
}



/***********************************************************************
                       Fast Ray-Box Intersection
                           by Andrew Woo
              from "Graphics Gems", Academic Press, 1990
***********************************************************************/
bool lineBoxCollision(sf::FloatRect box, sf::FloatRect ray, sf::Vector2f *coord, sf::Vector2f *normal, float *dist)
{
	bool inside = true;
	sf::Vector2i quadrant;
	int whichPlane;
	sf::Vector2f maxT;
	sf::Vector2f candidatePlane;


	if(ray.left < box.left) {
		quadrant.x = LEFT;
		candidatePlane.x = box.left;
		inside = false;
	} else if (ray.left > box.left + box.width) {
		quadrant.x = RIGHT;
		candidatePlane.x = box.left + box.width;
		inside = false;
	} else {
		quadrant.x = MIDDLE;
	}

	if(ray.top < box.top) {
		quadrant.y = LEFT;
		candidatePlane.y = box.top;
		inside = false;
	} else if (ray.top > box.top + box.height) {
		quadrant.y = RIGHT;
		candidatePlane.y = box.top + box.height;
		inside = false;
	} else {
		quadrant.y = MIDDLE;
	}


	if(inside)	{
		*coord = sf::Vector2f(ray.left, ray.top);
		return true;
	}


	if (quadrant.x != MIDDLE && ray.width !=0.)
		maxT.x = (candidatePlane.x - ray.left) / ray.width;
	else
		maxT.x = -1.;

	if (quadrant.y != MIDDLE && ray.height !=0.)
		maxT.y = (candidatePlane.y - ray.top) / ray.height;
	else
		maxT.y = -1.;


	whichPlane = 0;
	if (maxT.x < maxT.y)
		whichPlane = 1;


	if (whichPlane == 0) {
		if (maxT.x < 0.) return false;
	} else {
		if (maxT.y < 0.) return false;
	}

	if (whichPlane == 0) {
		coord->x = candidatePlane.x;
		coord->y = ray.top + maxT.x * ray.height;

		normal->x = quadrant.x;
		normal->y = 0;

		if (coord->y < box.top || coord->y > (box.top + box.height)) return false;
	} else {
		coord->x = ray.left + maxT.y * ray.width;
		coord->y = candidatePlane.y;

		normal->x = 0;
		normal->y = quadrant.y;

		if (coord->x < box.left || coord->x > (box.left + box.width)) return false;
	}

	if (dist) {
		 *dist = vLen(sf::Vector2f(coord->x - ray.left, coord->y - ray.top));
		 if (*dist > vLen(sf::Vector2f(ray.width, ray.height))) return false;
	}
	return true;
}
