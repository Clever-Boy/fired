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
		mlInfo,
		mlWarning,
		mlCritical
	};


	struct LogMessage {
		fired::LogMessageLevel level;
		char                   text[64];
		float                  life;


		LogMessage(const char *_text, fired::LogMessageLevel _level);

		bool update();
	};
}

#endif
