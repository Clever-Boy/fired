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
		sf::Vector2f origin;
		sf::Vector2f end;
		sf::Vector2f direction;
		float        angle;


		ModelBone(sf::Vector2f _origin, sf::Vector2f _direction);

		void reset();
		void rotate(float rotation);
		sf::Vector2f getEnd();
	};
}

#endif
