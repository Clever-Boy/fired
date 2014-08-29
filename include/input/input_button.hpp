/***********************************************************************
     * File       : input_button.hpp
     * Created    : Aug 27, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __INPUT_BUTTON
#define __INPUT_BUTTON


namespace fired {
	struct InputButton {
		fired::Window *parent;
		fired::Window *border;
		sf::FloatRect  rect;

		sf::Vector2f position;
		sf::Vector2f size;

		char caption[128];


		 InputButton(sf::Vector2f _size, sf::Vector2f _position, const char *_caption, fired::Window *_parent);
		~InputButton();

		void update();
		void render();

		void setSize(sf::Vector2f _size);
		void setPosition(sf::Vector2f _position);
	};
}

#endif
