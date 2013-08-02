#ifndef __SPLASH
#define __SPLASH


namespace fired {
	class ParticleSystemSplash: public ParticleSystem {
	public:
		void init();
		bool update();
		void deinit();
	};
}

#endif

