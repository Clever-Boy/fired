/***********************************************************************
     * File       : input_button.cpp
     * Created    : Aug 28, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * InputButton
     * constructor

***********************************************************************/
fired::InputButton::InputButton(sf::Vector2f _size, sf::Vector2f _position, const char *_caption, fired::Window *_parent) {
	parent   = _parent;
	size     = _size;
	position = _position + parent->offset;

	strncpy(caption, _caption, sizeof(caption));
	rect = sf::FloatRect(position, size);

	border = new fired::Window(size);
	border->setOffset(position);
	border->text->setCharacterSize(16);
}



/***********************************************************************
     * InputButton
     * destructor

***********************************************************************/
fired::InputButton::~InputButton() {
	delete border;
}



/***********************************************************************
     * InputButton
     * update

***********************************************************************/
void fired::InputButton::update() {
	render();
}



/***********************************************************************
     * InputButton
     * render

***********************************************************************/
void fired::InputButton::render() {
	border->render();
	border->renderText(size.x / 2, size.y / 2 - 12, caption, taCenter);
}
