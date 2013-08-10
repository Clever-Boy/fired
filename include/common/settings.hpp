#ifndef __SETTINGS
#define __SETTINGS


namespace fired {
	class Settings {
	public:
		struct {
			unsigned int width;
			unsigned int height;
			int bpp;
			bool fullScreen;
		} window;

		struct {
			int music;
			int sound;
		} volume;


		 Settings();
		~Settings();

		void save();
		void loadFromFile(const char *filename);
		void saveToFile(const char *filename);
	};
}

#endif
