/***********************************************************************
     * File       : win_base.cpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"




/***********************************************************************
     * Window
     * constructor

***********************************************************************/
fired::Window::Window(sf::Vector2f _size) {
	size   = _size;
	offset = sf::Vector2f((settings->window.width - size.x) / 2.0f, (settings->window.height - size.y) / 2.0f);

	window = new sf::RectangleShape(size);
	window->setPosition(offset);
	window->setFillColor(sf::Color(0, 0, 0, 200));
	window->setOutlineThickness(2);
	window->setOutlineColor(sf::Color(44, 88, 22));

	text = new sf::Text();
	text->setFont(*resources->fonts.game);
	text->setColor(sf::Color::White);
}



/***********************************************************************
     * Window
     * destructor

***********************************************************************/
fired::Window::~Window() {
	delete window;
	delete text;
}



/***********************************************************************
     * Window
     * render

***********************************************************************/
void fired::Window::render() {
	if (offset.x < 0) offset.x = 0;
	if (offset.y < 0) offset.y = 0;

	if (offset.x + size.x > settings->window.width ) offset.x = settings->window.width  - size.x;
	if (offset.y + size.y > settings->window.height) offset.y = settings->window.height - size.y;

	window->setPosition(offset);
	app->draw(*window);
}



/***********************************************************************
     * Window
     * render

***********************************************************************/
void fired::Window::renderText(float x, float y, const char *caption, fired::TextAlignment alignment, sf::Color color) {
	text->setColor(color);
	text->setString(sf::String(caption));

	sf::Vector2f textPosition = sf::Vector2f(x, y) + offset;

	switch (alignment) {
		case taLeft:
			break;

		case taRight:
			textPosition.x -= text->getGlobalBounds().width;
			break;

		case taCenter:
			textPosition.x -= text->getGlobalBounds().width / 2;
			break;
	}

	text->setPosition(textPosition);
	app->draw(*text);
}

/***********************************************************************
     * Window
     * setOffset

***********************************************************************/
void fired::Window::setOffset(sf::Vector2f newOffset) {
	offset = newOffset;
}



/***********************************************************************
     * Window
     * setSize

***********************************************************************/
void fired::Window::setSize(sf::Vector2f newSize) {
	size = newSize;
	window->setSize(size);
}
