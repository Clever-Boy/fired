/***********************************************************************
     * File       : weather_lightning.hpp
     * Created    : Feb 24, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WEATHER_LIGHTNING
#define __WEATHER_LIGHTNING


namespace fired {
	struct LightningLine {
		sf::Vector2f A, B;

		LightningLine() {};
		LightningLine(sf::Vector2f a, sf::Vector2f b) {A = a; B = b;};
	};


	struct Lightning {
		std::vector<sf::Vertex> line;

		 Lightning(sf::Vector2f start, sf::Vector2f dir);
		~Lightning();

		void draw();
	};
}

#endif

