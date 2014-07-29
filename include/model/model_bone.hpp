/***********************************************************************
     * File       : model_bone.hpp
     * Created    : Jul 28, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MODEL_BONE
#define __MODEL_BONE


namespace fired {
	struct ModelBone {
		sf::Vector2f start;
		sf::Vector2f end;
		sf::Vector2f origin;
		sf::Vector2f direction;
		float        angle;


		void reset();
		void set(sf::Vector2f _start, sf::Vector2f _end);
		void move(sf::Vector2f _move);
		void moveto(sf::Vector2f pos);
		void rotate(float rotation);
		void setRotation(float rotation);
		sf::Vector2f getEnd();
		sf::Vector2f getEndOffset();
	};
}

#endif
