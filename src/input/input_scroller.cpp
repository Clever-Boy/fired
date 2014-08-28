/***********************************************************************
     * File       : input_scroller.cpp
     * Created    : Aug 28, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * InputScroller
     * constructor

***********************************************************************/
fired::InputScroller::InputScroller(sf::Vector2f _size, sf::Vector2f _position, int _min, int _max, int _val, fired::Window *_parent) {
	parent   = _parent;
	size     = _size;
	position = _position + parent->offset;
	min      = _min;
	max      = _max;
	val      = _val;


	rect = sf::FloatRect(position, size);

	border = new fired::Window(size);
	border->setOffset(position);
	border->text->setCharacterSize(16);

	fill = new sf::RectangleShape();
	fill->setPosition(position);
	fill->setFillColor(sf::Color(207, 170, 24, 180));
}



/***********************************************************************
     * InputScroller
     * destructor

***********************************************************************/
fired::InputScroller::~InputScroller() {
	delete border;
	delete fill;
}



/***********************************************************************
     * InputScroller
     * update

***********************************************************************/
void fired::InputScroller::update() {
	fill->setSize(sf::Vector2f(size.x * ((float)val / (float)max), size.y));

	render();
}



/***********************************************************************
     * InputScroller
     * render

***********************************************************************/
void fired::InputScroller::render() {
	border->render();
	app->draw(*fill);

	char valStr[8];
	snprintf(valStr, sizeof(valStr), "%d", val);
	border->renderText(size.x / 2, size.y / 2 - 12, valStr, taCenter);
}



/***********************************************************************
     * InputScroller
     * click

***********************************************************************/
void fired::InputScroller::click(sf::Vector2f pos) {
	val = min + int((float)max * ((pos.x - position.x) / size.x));
}
