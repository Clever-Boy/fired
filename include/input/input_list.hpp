/***********************************************************************
     * File       : input_list.hpp
     * Created    : Aug 27, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __INPUT_LIST
#define __INPUT_LIST


namespace fired {
	struct InputList {
		fired::Window      *parent;
		fired::Window      *border;
		sf::FloatRect       rect;
		sf::RectangleShape *fill;

		sf::Vector2f position;
		sf::Vector2f size;

		std::vector<std::string> list;
		int                      index;
		int                      offset;


		 InputList(float _size, sf::Vector2f _position, int _offset, fired::Window *_parent);
		~InputList();

		void update();
		void render();
		void click(sf::Vector2f);
		void setSelected(const char *item);
		const char *getSelected();

		void setSize(float _size);
		void setPosition(sf::Vector2f _position);
	};
}

#endif
