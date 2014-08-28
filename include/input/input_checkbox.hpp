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
		fired::Window *parent;
		fired::Window *border;
		sf::FloatRect  rect;

		sf::Vector2f position;
		sf::Vector2f size;

		bool checked;


		 InputCheckbox() {};
		~InputCheckbox() {};

		void update() {};
		void render() {};
		void click(sf::Vector2f) {};
	};
}

#endif
