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
		fired::Window *parent;
		fired::Window *border;
		sf::FloatRect  rect;

		sf::Vector2f position;
		sf::Vector2f size;

		std::vector<std::string> list;


		 InputList() {};
		~InputList() {};

		void update() {};
		void render() {};
		void click(sf::Vector2f) {};
	};
}

#endif
