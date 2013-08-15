#include "game.hpp"

//======================================================================


float lessOrZero(float x) {
	if (x > 0) return 0;
	else return x;
};

//======================================================================


float sqr(float x) {
	return x * x;
}

//======================================================================


float sign(float x) {
	if (x > 0) return 1.0f;
	if (x < 0) return -1.0f;
	return 0.0f;
}

//======================================================================


sf::Vector2f vNorm(sf::Vector2f v) {
	return v / vLen(v);
}

//======================================================================


sf::Vector2f vSetLen(sf::Vector2f v, float l) {
	return vNorm(v) * l;
}

//======================================================================


sf::Vector2f rectCenter(sf::FloatRect rect) {
	return sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height / 2);
}

//======================================================================


float vLen(sf::Vector2f v) {
	return sqrt(sqr(v.x) + sqr(v.y));
}

//======================================================================


long levelXP(int level) {
	long res = 0;
	for (int i = 0; i < level; res += (i / 2 + 1) * 250, i++);
	return res;
}

//======================================================================


bool directoryContents(const char *dir, std::vector<std::string>* contents) {
	contents->clear();
	DIR *dir_ptr = opendir(dir);
	if (!dir_ptr) return false;

	dirent *dr;
	while ((dr = readdir(dir_ptr)))
		if (strcmp(dr->d_name, ".") &&
			strcmp(dr->d_name, "..") &&
			dr->d_name[0] != '.') 
				contents->push_back(dr->d_name);

	closedir(dir_ptr);
	return true;
}

/*======================================================================
                       Fast Ray-Box Intersection
                           by Andrew Woo
              from "Graphics Gems", Academic Press, 1990
======================================================================*/


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


	/* Calculate T distances to candidate planes */
	if (quadrant.x != MIDDLE && ray.width !=0.)
		maxT.x = (candidatePlane.x - ray.left) / ray.width;
	else
		maxT.x = -1.;

	if (quadrant.y != MIDDLE && ray.height !=0.)
		maxT.y = (candidatePlane.y - ray.top) / ray.height;
	else
		maxT.y = -1.;


	/* Get largest of the maxT's for final choice of intersection */
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
