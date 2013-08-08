#ifndef __MISC
#define __MISC


#include <math.h>
#include <SFML/Graphics.hpp>

#define NUMDIM	2
#define LEFT	-1
#define MIDDLE	0
#define RIGHT	1


float lessOrZero(float x);
float sqr(float x);
float sign(float x);
bool directoryContents(const char *dir, std::vector<std::string>* contents);
bool lineBoxCollision(sf::FloatRect box, sf::FloatRect ray, sf::Vector2f *coord, sf::Vector2f *normal, float *dist);

#endif
