#include "game.hpp"

void fired::Mouse::processEvent(sf::Event event) {
	return;
}


void fired::Mouse::render() {
	mouseCur.setPosition(pos);
	game->app.draw(mouseCur);
}


void fired::Mouse::init(fired::Game *_game) {
	game = _game;

	mouseTex.loadFromFile("data/img/gui/mainmenu/mouse.png");
	mouseCur.setTexture(mouseTex);
	mouseCur.setScale(20.0 / mouseTex.getSize().x, 24.0 / mouseTex.getSize().x);
	mouseTex.setSmooth(true);

	return;
}

void fired::Mouse::update(float frameClock) {
	pos = sf::Vector2f(sf::Mouse::getPosition(game->app));
	render();
}
