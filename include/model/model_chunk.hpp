/***********************************************************************
     * File       : model_chunk.hpp
     * Created    : Aug 09, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MODEL_CHUNK
#define __MODEL_CHUNK


#include "model_bodypart.hpp"


namespace fired {
	struct Chunk {
		fired::BaseBodypart *base;
		fired::World        *world;
		fired::Phys          phys;

		sf::Color    color;
		float        rotationSpeed;
		float        rotation;
		float        scaleX;
		float        scaleY;
		float        lifetime;


		Chunk(fired::Bodypart *bodyPart, float scale, sf::Vector2f position, sf::Vector2f speed, fired::World *_world);

		bool update();
		void render();
	};
}

#endif
