/***********************************************************************
     * File       : log_message.hpp
     * Created    : Jul 18, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __LOG_MESSAGE
#define __LOG_MESSAGE


namespace fired {
	enum LogMessageLevel {
		mlNeutral,
		mlInfo,
		mlWarning,
		mlCritical
	};


	struct LogMessage {
		sf::Color color;
		char      text[64];
		float     life;
		float     top;


		LogMessage(const char *_text, fired::LogMessageLevel level);

		bool update();
	};
}

#endif
