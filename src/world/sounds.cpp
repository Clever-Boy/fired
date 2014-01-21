#include "game.hpp"

//======================================================================


fired::GameSound::GameSound(const char *filename, const char *_name) {
	strcpy(name, _name);

	buf = new sf::SoundBuffer();
	buf->loadFromFile(filename);

	snd = new sf::Sound();
	snd->setBuffer(*buf);
	snd->setVolume(settings->volume.sound);
}

//======================================================================


fired::GameSound::~GameSound() {
	delete buf;
	delete snd;
}
