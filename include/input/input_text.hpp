/***********************************************************************
     * File       : input_text.hpp
     * Created    : Aug 27, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __INPUT_TEXT
#define __INPUT_TEXT


namespace fired {
	struct InputText {
		sf::FloatRect rect;

		sf::Vector2f position;
		sf::Vector2f size;

		char text[256];
		int  len;


		 InputText() {};
		~InputText() {};

		void update() {};
		void render() {};
	};
}

#endif
