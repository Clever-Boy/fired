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
fired::InputList::InputList(float _size, sf::Vector2f _position, int _offset, fired::Window *_parent) {
	parent   = _parent;
	offset   = _offset;
	size     = sf::Vector2f(_size, 20 * (offset * 2 + 1));
	position = _position + parent->offset;
	index    = 0;

	rect = sf::FloatRect(position, size);
	list.clear();

	border = new fired::Window(size);
	border->setOffset(position);
	border->text->setCharacterSize(16);

	fill = new sf::RectangleShape(sf::Vector2f(_size, 20));
	fill->setPosition(position + sf::Vector2f(0, 20 * offset));
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

	for (int i = -offset; i <= offset; i++) {
		itemIndex = index  + i;
		drawIndex = offset + i;

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
	int newIndex = index + ((int)((pos.y - position.y) / 20) - offset);
	if (newIndex >= 0 && newIndex < (int)list.size()) index = newIndex;
}



/***********************************************************************
     * InputList
     * setSelected

***********************************************************************/
void fired::InputList::setSelected(const char *item) {
	for (unsigned int i = 0; i < list.size(); i++)
		if (!strcmp(list[i].c_str(), item)) {
			index = i;
			break;
		}
}
