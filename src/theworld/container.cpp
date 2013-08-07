#include "game.hpp"

//======================================================================


void fired::Container::init(fired::Game *_game, fired::World *_world) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	world    = _world;

	loadWeapons();
}

//======================================================================


void fired::Container::deinit() {
	for (int i = 0; i < weapons.size(); i++) {
		weapons[i]->deinit();
		delete weapons[i];
	}

	weapons.clear();
}

//======================================================================


void fired::Container::loadWeapons() {
	std::vector<std::string> files;
	char filename[128];

	directoryContents("data/game/weapons", &files);
	for (int i = 0; i < files.size(); i++) {
		snprintf(filename, sizeof(filename), "data/game/weapons/%s", files[i].c_str());
		loadWeapon(filename);
	}
}

//======================================================================


void fired::Container::loadWeapon(const char* filename) {
	char sndfile[128];
	char sndpath[128];
	weapons.push_back(new fired::BaseWeapon);

	FILE *fp = fopen(filename, "r");
	fscanf(fp, "weapon.name=%s\n"    , weapons.back()->name);
	fscanf(fp, "weapon.damage=%u\n"  , &weapons.back()->damage);
	fscanf(fp, "weapon.cooldown=%f\n", &weapons.back()->cooldown);
	fscanf(fp, "weapon.fire=%s\n"    , sndfile);
	fclose(fp);

	snprintf(sndpath, sizeof(sndpath), "data/snd/weapons/%s", sndfile);
	weapons.back()->shotBuffer = new sf::SoundBuffer();
	weapons.back()->shotBuffer->loadFromFile(sndpath);

	weapons.back()->shotSound = new sf::Sound();
	weapons.back()->shotSound->setBuffer(*weapons.back()->shotBuffer);
	weapons.back()->shotSound->setVolume(game->getSettings()->volume.sound);
}

//======================================================================


fired::BaseWeapon* fired::Container::getWeapon(const char* name) {
	for (int i = 0; i < weapons.size(); i++)
		if (!strcmp(name, weapons[i]->name)) return weapons[i];

	return NULL;
}
