/***********************************************************************
     * File       : input_checkbox.hpp
     * Created    : Aug 27, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __INPUT_CHECKBOX
#define __INPUT_CHECKBOX


namespace fired {
	struct InputCheckbox {
		fired::Window      *parent;
		fired::Window      *border;
		sf::FloatRect       rect;
		sf::RectangleShape *fill;

		sf::Vector2f position;
		sf::Vector2f size;

		bool val;


		 InputCheckbox(sf::Vector2f _position, bool _val, fired::Window *_parent);
		~InputCheckbox();

		void update();
		void render();
		void click();
	};
}

#endif
