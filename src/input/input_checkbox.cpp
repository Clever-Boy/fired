/***********************************************************************
     * File       : input_checkbox.cpp
     * Created    : Aug 28, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * InputCheckbox
     * constructor

***********************************************************************/
fired::InputCheckbox::InputCheckbox(sf::Vector2f _position, bool _val, fired::Window *_parent) {
	parent   = _parent;
	size     = sf::Vector2f(16, 16);
	position = _position + parent->offset;
	val      = _val;


	rect = sf::FloatRect(position, size);

	border = new fired::Window(size);
	border->setOffset(position);

	fill = new sf::RectangleShape(size);
	fill->setPosition(position);
	fill->setFillColor(sf::Color(207, 170, 24, 180));
}



/***********************************************************************
     * InputCheckbox
     * destructor

***********************************************************************/
fired::InputCheckbox::~InputCheckbox() {
	delete border;
	delete fill;
}



/***********************************************************************
     * InputCheckbox
     * update

***********************************************************************/
void fired::InputCheckbox::update() {
	render();
}



/***********************************************************************
     * InputCheckbox
     * render

***********************************************************************/
void fired::InputCheckbox::render() {
	border->render();
	if (val) app->draw(*fill);
}



/***********************************************************************
     * InputCheckbox
     * click

***********************************************************************/
void fired::InputCheckbox::click() {
	val = !val;
}



/***********************************************************************
     * InputCheckbox
     * setPosition

***********************************************************************/
void fired::InputCheckbox::setPosition(sf::Vector2f _position) {
	position = _position + parent->offset;
	rect     = sf::FloatRect(position, size);

	border->setOffset(position);
	fill->setPosition(position);
}
