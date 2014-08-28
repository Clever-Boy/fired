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
		fired::Window      *parent;
		fired::Window      *border;
		sf::FloatRect       rect;
		sf::RectangleShape *fill;

		sf::Vector2f position;
		sf::Vector2f size;

		char text[256];
		bool focused;
		int  lenMax;
		int  len;


		 InputText(float _size, sf::Vector2f _position, int _lenMax, fired::Window *_parent);
		~InputText();

		void update();
		void render();
		void click();
		void textEntered(sf::Uint32 c);
	};
}

#endif
