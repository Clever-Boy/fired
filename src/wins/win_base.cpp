#include "game.hpp"

//======================================================================


fired::Window::Window(sf::Vector2f _size) {
	size   = _size;
	offset = sf::Vector2f((settings->window.width - size.x) / 2.0f, (settings->window.height - size.y) / 2.0f);

	window = new sf::RectangleShape(size);
	window->setPosition(offset);
	window->setFillColor(sf::Color(0, 0, 0, 200));
	window->setOutlineThickness(2);
	window->setOutlineColor(sf::Color(44, 88, 22));
}

//======================================================================


fired::Window::~Window() {
	delete window;
}

//======================================================================


void fired::Window::render() {
	if (offset.x < 0) offset.x = 0;
	if (offset.y < 0) offset.y = 0;

	if (offset.x + size.x > settings->window.width ) offset.x = settings->window.width  - size.x;
	if (offset.y + size.y > settings->window.height) offset.y = settings->window.height - size.y;

	window->setPosition(offset);
	app->draw(*window);
}

//======================================================================


void fired::Window::setOffset(sf::Vector2f newOffset) {
	offset = newOffset;
}

//======================================================================


void fired::Window::setSize(sf::Vector2f newSize) {
	size = newSize;
	window->setSize(size);
}
