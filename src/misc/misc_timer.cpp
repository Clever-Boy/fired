/***********************************************************************
     * File       : misc_timer.cpp
     * Created    : Jun 29, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Timer
     * setTimer

***********************************************************************/
void fired::Timer::setTimer(float _timer) {
	timer = _timer;
	value = _timer;
}



/***********************************************************************
     * Timer
     * reset

***********************************************************************/
void fired::Timer::reset() {
	value = timer;
}



/***********************************************************************
     * Timer
     * process

***********************************************************************/
bool fired::Timer::process() {
	if (value == 0) return false;

	value -= frameClock;
	if (value <= 0) {
		value = 0;
		return false;
	} else
		return true;
}



/***********************************************************************
     * Timer
     * isActive

***********************************************************************/
bool fired::Timer::isActive() {
	if (value == 0) return false;
	return true;
}



/***********************************************************************
     * Timer
     * getPercent

***********************************************************************/
float fired::Timer::getPercent() {
	if (timer == 0) return 0;

	return (1.0f - value / timer);
}
