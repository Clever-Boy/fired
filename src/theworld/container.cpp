#include "game.hpp"

//======================================================================


void fired::Container::init(fired::Game *_game, fired::World *_world) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	world    = _world;

	loadWeapons();
	loadBodyparts();
}

//======================================================================


void fired::Container::deinit() {
	for (int i = 0; i < weapons.size(); i++) {
		weapons[i]->deinit();
		delete weapons[i];
	}

	for (int i = 0; i < bodyparts.size(); i++) {
		bodyparts[i]->deinit();
		delete bodyparts[i];
	}


	weapons.clear();
	bodyparts.clear();
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
	fscanf(fp, "name=%s\n"    , weapons.back()->name);
	fscanf(fp, "damage=%u\n"  , &weapons.back()->damage);
	fscanf(fp, "cooldown=%f\n", &weapons.back()->cooldown);
	fscanf(fp, "fire=%s\n"    , sndfile);
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

//======================================================================


void fired::Container::loadBodyparts() {
	loadBodypartsInDir("arms"  , bptArms);
	loadBodypartsInDir("body"  , bptBody);
	loadBodypartsInDir("head"  , bptHead);
	loadBodypartsInDir("hair"  , bptHair);
	loadBodypartsInDir("fistF" , bptFistF);
	loadBodypartsInDir("fistB" , bptFistB);
	loadBodypartsInDir("legsF" , bptLegsF);
	loadBodypartsInDir("legsB" , bptLegsB);
	loadBodypartsInDir("shoeF" , bptShoeF);
	loadBodypartsInDir("shoeB" , bptShoeB);
	loadBodypartsInDir("weapon", bptWeapon);
}

//======================================================================


void fired::Container::loadBodypartsInDir(const char *dir, fired::BodypartType type) {
	std::vector<std::string> files;
	char dirname[128];
	char filename[128];

	snprintf(dirname, sizeof(dirname), "data/game/bodyparts/%s", dir);
	directoryContents(dirname, &files);
	for (int i = 0; i < files.size(); i++) {
		snprintf(filename, sizeof(filename), "data/game/bodyparts/%s/%s", dir, files[i].c_str());
		loadBodypart(dir, filename, type);
	}
}

//======================================================================


void fired::Container::loadBodypart(const char *dir, const char* filename, fired::BodypartType type) {
	char imgfile[128];
	char imgpath[128];
	bodyparts.push_back(new fired::Bodypart);

	FILE *fp = fopen(filename, "r");
	fscanf(fp, "name=%s\n"     , bodyparts.back()->name);
	fscanf(fp, "offset=%f,%f\n", &bodyparts.back()->offset.x, &bodyparts.back()->offset.y);
	fscanf(fp, "color=%d,%d,%d,%d\n", &bodyparts.back()->color.r, &bodyparts.back()->color.g, &bodyparts.back()->color.b, &bodyparts.back()->color.a);
	fscanf(fp, "image=%s\n"    , imgfile);
	fclose(fp);

	snprintf(imgpath, sizeof(imgpath), "data/img/world/models/%s/%s", dir, imgfile);
	bodyparts.back()->texture = new sf::Texture;
	bodyparts.back()->texture->loadFromFile(imgpath);
	bodyparts.back()->texture->setSmooth(true);

	bodyparts.back()->sprite = new sf::Sprite;
	bodyparts.back()->sprite->setTexture(*bodyparts.back()->texture);
	bodyparts.back()->type = type;
}

//======================================================================


fired::Bodypart* fired::Container::getBodypart(const char* name) {
	return NULL;
}
