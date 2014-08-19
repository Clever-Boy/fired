/***********************************************************************
     * File       : log_message.cpp
     * Created    : Aug 19, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * LogMessage
     * constructor

***********************************************************************/
fired::LogMessage::LogMessage(const char *_text, fired::LogMessageLevel level) {
	top   = LOG_MESSAGE_HEIGHT * (LOG_SIZE - 1);
	life  = LOG_MESSAGE_LIFE;
	strncpy(text, _text, 64);

	switch (level) {
		case mlNeutral : color = sf::Color(255, 255, 255); break;
		case mlInfo    : color = sf::Color(  0, 255,   0); break;
		case mlWarning : color = sf::Color(255, 255,   0); break;
		case mlCritical: color = sf::Color(255,   0,   0); break;
	}
}



/***********************************************************************
     * LogMessage
     * update

***********************************************************************/
bool fired::LogMessage::update() {
	life -= frameClock;
	top  -= frameClock * LOG_MESSAGE_SPEED;

	if (life <= 0.0f) return false;
	if (life <= LOG_MESSAGE_FADING) color.a = 255 * (life / LOG_MESSAGE_FADING);

	return true;
}
