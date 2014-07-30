/***********************************************************************
     * File       : misc_timer.hpp
     * Created    : Jun 29, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MISC_TIMER
#define __MISC_TIMER


namespace fired {
	struct Timer {
		float value;
		float timer;


		Timer() { value = 0.0f; timer = 0.0f; };

		void  setTimer(float _timer);
		bool  process();
		bool  isActive();
		float getPercent();
	};
}

#endif
