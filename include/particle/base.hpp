#ifndef __BASE
#define __BASE


namespace fired {
	class ParticleSystem {
	private:
		int life;

	public:
		virtual void init()   {return; };
		virtual void update() {return; };
		virtual void render() {return; };
		virtual void deinit() {return; };
	};
}

#endif
