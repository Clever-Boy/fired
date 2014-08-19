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
fired::LogMessage::LogMessage(const char *_text, fired::LogMessageLevel _level) {
	life  = 0.0f;
	level = _level;

	strncpy(text, _text, 64);
}



/***********************************************************************
     * LogMessage
     * update

***********************************************************************/
bool fired::LogMessage::update() {
	life += frameClock;
	return true;
}
