#ifndef __MISC
#define __MISC


float lessOrZero(float x);
float sqr(float x);
float sign(float x);
bool directoryContents(const char *dir, std::vector<std::string>* contents);
bool lineBoxCollision(sf::FloatRect box, sf::FloatRect ray, sf::Vector2f *coord, sf::Vector2f *normal, float *dist);
long levelXP(int level);


sf::Vector2f vNorm(sf::Vector2f v);
sf::Vector2f vSetLen(sf::Vector2f v, float l);
sf::Vector2f rectCenter(sf::FloatRect rect);
float        vLen(sf::Vector2f v);

#endif
