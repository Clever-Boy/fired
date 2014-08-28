/***********************************************************************
     * File       : input_text.cpp
     * Created    : Aug 28, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * InputText
     * constructor

***********************************************************************/
fired::InputText::InputText(float _size, sf::Vector2f _position, int _lenMax, fired::Window *_parent) {
	parent   = _parent;
	size     = sf::Vector2f(_size, 20);
	position = _position + parent->offset;
	lenMax   = _lenMax;
	len      = 0;

	memset(text, 0, sizeof(text));
	rect = sf::FloatRect(position, size);

	border = new fired::Window(size);
	border->setOffset(position);
	border->text->setCharacterSize(16);

	fill = new sf::RectangleShape(sf::Vector2f(8, 16));
	fill->setFillColor(sf::Color(207, 170, 24, 180));
	fill->setPosition(position + sf::Vector2f(border->getTextSize(text) + 2, 2));
}



/***********************************************************************
     * InputText
     * destructor

***********************************************************************/
fired::InputText::~InputText() {
	delete border;
	delete fill;
}



/***********************************************************************
     * InputText
     * update

***********************************************************************/
void fired::InputText::update() {
	render();
}



/***********************************************************************
     * InputText
     * render

***********************************************************************/
void fired::InputText::render() {
	border->render();
	border->renderText(0, 0, text, taLeft);
	if (focused) app->draw(*fill);
}



/***********************************************************************
     * InputText
     * click

***********************************************************************/
void fired::InputText::click() {
	focused = true;
}



/***********************************************************************
     * InputText
     * textEntered

***********************************************************************/
void fired::InputText::textEntered(sf::Uint32 c) {
	if (c > 128) return;
	char _c = static_cast<char>(c);

	if (backspaceChar(_c))
		text[--len] = 0;
	else if (printableChar(_c) && len != lenMax)
		text[len++] = _c;

	fill->setPosition(position + sf::Vector2f(border->getTextSize(text) + 2, 2));
}
