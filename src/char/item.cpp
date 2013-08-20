#include "game.hpp"


void fired::BaseInventoryItem::render(sf::Vector2f pos) {
	sprite->setPosition(pos);
	app->draw(*sprite);
}
