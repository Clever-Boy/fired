#ifndef __CONE
#define __CONE


namespace fired {
	class ParticleSystemCone: public ParticleSystem {
	public:
		virtual void init();
		virtual void update();
		virtual void render();
		virtual void deinit();
	};
}

#endif

