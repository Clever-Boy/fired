/***********************************************************************
     * File       : log_base.hpp
     * Created    : Jul 18, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __LOG_BASE
#define __LOG_BASE


namespace fired {
	struct Log {
		std::vector<fired::LogMessage *>  messages;
		fired::Window                    *win;


		 Log(sf::FloatRect rect);
		~Log();

		void update();
		void render();
	};
}

#endif
