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
		sf::FloatRect rect;

		sf::Vector2f position;
		sf::Vector2f size;

		int min;
		int max;
		int val;


		 InputScroller() {};
		~InputScroller() {};

		void update() {};
		void render() {};
		void click(sf::Vector2f) {};
	};
}

#endif
