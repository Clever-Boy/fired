/***********************************************************************
     * File       : model_bone.cpp
     * Created    : Jul 28, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * ModelBone
     * set

***********************************************************************/
void fired::ModelBone::set(sf::Vector2f _origin, sf::Vector2f _end) {
	origin    = _origin;
	end       = _end;
	direction = _end - _origin;
	angle     = 0;
}



/***********************************************************************
     * ModelBone
     * getEnd

***********************************************************************/
sf::Vector2f fired::ModelBone::getEnd() {
	return origin + direction;
}



/***********************************************************************
     * ModelBone
     * rotate

***********************************************************************/
void fired::ModelBone::rotate(float rotation) {
	direction = sf::Vector2f(
		direction.x * cos(rotation) - direction.y * sin(rotation),
		direction.x * sin(rotation) + direction.y * cos(rotation)
	);

	angle += rotation;
}



/***********************************************************************
     * ModelBone
     * reset

***********************************************************************/
void fired::ModelBone::reset() {
	direction = end - origin;
	angle = 0.0f;
}
