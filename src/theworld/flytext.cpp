#include "game.hpp"

//======================================================================


void fired::FlyText::init(fired::Game *_game, sf::Vector2f _pos, sf::Color _color, int size, const char *text) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	pos      = _pos;
	color    = _color;
	life     = 0;

	flyStr = new sf::String(text);
	flyTxt = new sf::Text;
	flyTxt->setFont(*game->getFont());
	flyTxt->setString(*flyStr);
	flyTxt->setCharacterSize(size);
	flyTxt->setStyle(sf::Text::Bold);
}

//======================================================================


void fired::FlyText::deinit() {
	delete flyStr;
	delete flyTxt;
}

//======================================================================


bool fired::FlyText::update() {
	life += frameClock;

	if (life > FLYTEXT_LIFETIME / 2)
		color.a = 255 * (0.5 - life / FLYTEXT_LIFETIME);
	else
		color.a = 255;

	if (life > FLYTEXT_LIFETIME) return false;

	render();
	return true;
}

//======================================================================


void fired::FlyText::render() {
	flyTxt->setPosition(pos - sf::Vector2f(0, life * FLYTEXT_OFFSET / FLYTEXT_LIFETIME));
	flyTxt->setColor(color);
	app->draw(*flyTxt);
}