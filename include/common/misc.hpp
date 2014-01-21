#ifndef __MISC
#define __MISC


void swapItems(fired::InventoryItem *item1, fired::InventoryItem *item2);
void emptyItem(fired::InventoryItem *item);
float lessOrZero(float x);
float sqr(float x);
float sign(float x);
bool directoryContents(const char *dir, std::vector<std::string>* contents);
bool lineBoxCollision(sf::FloatRect box, sf::FloatRect ray, sf::Vector2f *coord, sf::Vector2f *normal, float *dist);

#endif
