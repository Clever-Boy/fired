/***********************************************************************
     * File       : input_list.cpp
     * Created    : Aug 28, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * InputList
     * constructor

***********************************************************************/
fired::InputList::InputList(float _size, sf::Vector2f _position, fired::Window *_parent) {
	parent   = _parent;
	size     = sf::Vector2f(_size, 140);
	position = _position + parent->offset;
	index    = 0;

	rect = sf::FloatRect(position, size);
	list.clear();

	border = new fired::Window(size);
	border->setOffset(position);
	border->text->setCharacterSize(16);

	fill = new sf::RectangleShape(sf::Vector2f(_size, 20));
	fill->setPosition(position + sf::Vector2f(0, 60));
	fill->setFillColor(sf::Color(207, 170, 24, 180));
}



/***********************************************************************
     * InputList
     * destructor

***********************************************************************/
fired::InputList::~InputList() {
	delete border;
	delete fill;

	list.clear();
}



/***********************************************************************
     * InputList
     * update

***********************************************************************/
void fired::InputList::update() {
	render();
}



/***********************************************************************
     * InputList
     * render

***********************************************************************/
void fired::InputList::render() {
	border->render();
	app->draw(*fill);

	if (list.size() == 0) return;

	int drawIndex;
	int itemIndex;

	for (int i = -3; i <= 3; i++) {
		itemIndex = index + i;
		drawIndex = 3     + i;

		if (itemIndex < 0) continue;
		if (itemIndex >= (int)list.size()) break;

		border->renderText(size.x / 2, (drawIndex) * 20 + 2, list[itemIndex].c_str(), taCenter);
	}
}



/***********************************************************************
     * InputList
     * click

***********************************************************************/
void fired::InputList::click(sf::Vector2f pos) {
	int newIndex = index + ((int)((pos.y - position.y) / 20) - 3);
	if (newIndex >= 0 && newIndex < (int)list.size()) index = newIndex;
}
