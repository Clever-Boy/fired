/***********************************************************************
     * File       : input_scroller.hpp
     * Created    : Aug 27, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __INPUT_SCROLLER
#define __INPUT_SCROLLER


namespace fired {
	struct InputScroller {
		fired::Window      *parent;
		fired::Window      *border;
		sf::FloatRect       rect;
		sf::RectangleShape *fill;

		sf::Vector2f position;
		sf::Vector2f size;

		int min;
		int max;
		int val;


		 InputScroller(sf::Vector2f _size, sf::Vector2f _position, int _min, int _max, int _val, fired::Window *_parent);
		~InputScroller();

		void update();
		void render();
		void click(sf::Vector2f pos);

		void setSize(sf::Vector2f _size);
		void setPosition(sf::Vector2f _position);
	};
}

#endif
