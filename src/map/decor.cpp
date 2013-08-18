#include "game.hpp"


//======================================================================


void fired::Decor::render() {
	sprite->setPosition(pos);
	sprite->setColor(color);
	app->draw(*sprite);
}
