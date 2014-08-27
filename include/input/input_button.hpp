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
		sf::FloatRect rect;

		sf::Vector2f position;
		sf::Vector2f size;


		 InputButton() {};
		~InputButton() {};

		void update() {};
		void render() {};
		void click(sf::Vector2f) {};
	};
}

#endif
