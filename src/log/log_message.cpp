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
	life  = 0.0f;
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
	life += frameClock;
	return true;
}
