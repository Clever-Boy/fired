#include "game.hpp"

//======================================================================


void fired::Container::init(fired::Game *_game, fired::World *_world) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	world    = _world;

	loadWeapons();
	loadBodyparts();
	loadModels();
	loadCreatures();
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

	for (int i = 0; i < models.size(); i++)
		delete models[i];

	for (int i = 0; i < creatures.size(); i++)
		delete creatures[i];


	weapons.clear();
	bodyparts.clear();
	models.clear();
	creatures.clear();
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
	fscanf(fp, "name=%s\n"     , weapons.back()->name);
	fscanf(fp, "damage=%u\n"   , &weapons.back()->damage);
	fscanf(fp, "cooldown=%f\n" , &weapons.back()->cooldown);
	fscanf(fp, "knockback=%f\n", &weapons.back()->knockback);
	fscanf(fp, "fire=%s\n"     , sndfile);
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
	bodyparts.push_back(new fired::BaseBodypart);

	FILE *fp = fopen(filename, "r");
	fscanf(fp, "name=%s\n"     , bodyparts.back()->name);
	fscanf(fp, "offset=%f,%f\n", &bodyparts.back()->offset.x, &bodyparts.back()->offset.y);
	fscanf(fp, "color=%hhu,%hhu,%hhu,%hhu\n", &bodyparts.back()->color.r, &bodyparts.back()->color.g, &bodyparts.back()->color.b, &bodyparts.back()->color.a);
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


fired::BaseBodypart* fired::Container::getBodypart(const char* name, fired::BodypartType type) {
	for (int i = 0; i < bodyparts.size(); i++)
		if (!strcmp(name, bodyparts[i]->name) && type == bodyparts[i]->type) return bodyparts[i];

	return NULL;
}

//======================================================================


void fired::Container::loadModels() {
	std::vector<std::string> files;
	char filename[128];

	directoryContents("data/game/models", &files);
	for (int i = 0; i < files.size(); i++) {
		snprintf(filename, sizeof(filename), "data/game/models/%s", files[i].c_str());
		loadModel(filename);
	}
}

//======================================================================


void fired::Container::loadModel(const char* filename) {
	char field[128];

	FILE *fp = fopen(filename, "r");
	fscanf(fp, "type=%s\n", field);

	if (!strcmp(field, "humanoid")) {
		fired::BaseModelHumanoid *model = new fired::BaseModelHumanoid;
		model->type = mtHumanoid;
		fscanf(fp, "name=%s\n"    , model->name);
		fscanf(fp, "size=%f,%f\n", &model->size.x, &model->size.y);

		fscanf(fp, "legsf=%s\n", field);
		model->partLegsF = getBodypart(field, bptLegsF);

		fscanf(fp, "legsb=%s\n", field);
		model->partLegsB = getBodypart(field, bptLegsB);

		fscanf(fp, "shoef=%s\n", field);
		model->partShoeF = getBodypart(field, bptShoeF);

		fscanf(fp, "shoeb=%s\n", field);
		model->partShoeB = getBodypart(field, bptShoeB);

		fscanf(fp, "fistf=%s\n", field);
		model->partFistF = getBodypart(field, bptFistF);

		fscanf(fp, "fistb=%s\n", field);
		model->partFistB = getBodypart(field, bptFistB);

		fscanf(fp, "arms=%s\n", field);
		model->partArms = getBodypart(field, bptArms);

		fscanf(fp, "hair=%s\n", field);
		model->partHair = getBodypart(field, bptHair);

		fscanf(fp, "head=%s\n", field);
		model->partHead = getBodypart(field, bptHead);

		fscanf(fp, "body=%s\n", field);
		model->partBody = getBodypart(field, bptBody);

		fscanf(fp, "weapon=%s\n", field);
		model->partWeapon = getBodypart(field, bptWeapon);

		models.push_back(model);
	}
}

//======================================================================


fired::BaseModel* fired::Container::getModel(const char* name) {
	for (int i = 0; i < models.size(); i++)
		if (!strcmp(name, models[i]->name)) return models[i];

	return NULL;
}

//======================================================================


void fired::Container::loadCreatures() {
	std::vector<std::string> files;
	char filename[128];

	directoryContents("data/game/creatures", &files);
	for (int i = 0; i < files.size(); i++) {
		snprintf(filename, sizeof(filename), "data/game/creatures/%s", files[i].c_str());
		loadCreature(filename);
	}
}

//======================================================================


void fired::Container::loadCreature(const char* filename) {
	creatures.push_back(new fired::BaseCreature);

	FILE *fp = fopen(filename, "r");
	fscanf(fp, "name=%s\n"    ,  creatures.back()->name);
	fscanf(fp, "model=%s\n"   ,  creatures.back()->model);
	fscanf(fp, "scale=%f\n"   , &creatures.back()->modelScale);
	fscanf(fp, "weapon=%s\n"  ,  creatures.back()->weapon);
	fscanf(fp, "speed=%f\n"   , &creatures.back()->stats.speed);
	fscanf(fp, "accel=%f\n"   , &creatures.back()->stats.accel);
	fscanf(fp, "jump=%f\n"    , &creatures.back()->stats.jump);
	fscanf(fp, "aimrange=%f\n", &creatures.back()->stats.aimrange);
	fscanf(fp, "maxHP=%u\n"   , &creatures.back()->stats.maxHP);
	fclose(fp);
}

//======================================================================


fired::BaseCreature* fired::Container::getCreature(const char* name) {
	for (int i = 0; i < creatures.size(); i++)
		if (!strcmp(name, creatures[i]->name)) return creatures[i];

	return NULL;
}
