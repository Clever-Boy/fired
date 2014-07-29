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
void fired::ModelBone::set(sf::Vector2f _start, sf::Vector2f _end) {
	start     = _start;
	end       = _end;

	origin    = start;
	direction = end - start;

	angle     = 0.0f;
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
     * getEndOffset

***********************************************************************/
sf::Vector2f fired::ModelBone::getEndOffset() {
	return getEnd() - end;
}



/***********************************************************************
     * ModelBone
     * getEnd

***********************************************************************/
sf::Vector2f fired::ModelBone::getOriginOffset() {
	return origin - start;
}



/***********************************************************************
     * ModelBone
     * rotate

***********************************************************************/
void fired::ModelBone::rotate(float _rotation) {
	float rotation = _rotation * DEG_TO_RAD;

	direction = sf::Vector2f(
		direction.x * cos(rotation) - direction.y * sin(rotation),
		direction.x * sin(rotation) + direction.y * cos(rotation)
	);

	angle += _rotation;
}



/***********************************************************************
     * ModelBone
     * setRotation

***********************************************************************/
void fired::ModelBone::setRotation(float _rotation) {
	float rotation = _rotation * DEG_TO_RAD;

	direction = end - start;
	direction = sf::Vector2f(
		direction.x * cos(rotation) - direction.y * sin(rotation),
		direction.x * sin(rotation) + direction.y * cos(rotation)
	);

	angle = _rotation;
}



/***********************************************************************
     * ModelBone
     * reset

***********************************************************************/
void fired::ModelBone::reset() {
	origin    = start;
	direction = end - start;
	angle     = 0.0f;
}



/***********************************************************************
     * ModelBone
     * move

***********************************************************************/
void fired::ModelBone::move(sf::Vector2f _move) {
	origin += _move;
}



/***********************************************************************
     * ModelBone
     * moveto

***********************************************************************/
void fired::ModelBone::moveto(sf::Vector2f pos) {
	origin = pos;
}
