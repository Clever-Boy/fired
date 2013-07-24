#ifndef __SETTINGS
#define __SETTINGS


namespace fired {
	class Settings {
	public:
		struct {
			int width;
			int height;
			int bpp;
			bool fullScreen;
		} window;

		struct {
			int music;
			int sound;
		} volume;


		void init();
		void save();
		void loadFromFile(const char *filename);
		void saveToFile(const char *filename);
	};
}

#endif
