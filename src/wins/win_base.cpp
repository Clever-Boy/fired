#include "game.hpp"

//======================================================================


fired::Window::Window(sf::Vector2f _size) {
	size   = _size;
	offset = sf::Vector2f((settings->window.width - size.x) / 2.0f, (settings->window.height - size.y) / 2.0f);

	window = new sf::RectangleShape(size);
	window->setPosition(offset);
	window->setFillColor(sf::Color(0, 0, 0, 155));
	window->setOutlineThickness(2);
	window->setOutlineColor(sf::Color(44, 88, 22));
}

//======================================================================


fired::Window::~Window() {
	delete window;
}

//======================================================================


void fired::Window::render() {
	app->draw(*window);
}
