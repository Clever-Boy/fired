#include "game.hpp"

//======================================================================


fired::Container::Container(fired::World *_world) {
	world    = _world;

	loadBodyparts();
	loadWeapons();
	loadModels();
	loadCreatures();
	loadDecors();
}

//======================================================================


fired::Container::~Container() {
	deleteList(weapons);
	deleteList(bodyparts);
	deleteList(models);
	deleteList(creatures);
	deleteList(decors);
}

//======================================================================


void fired::Container::loadWeapons() {
	std::vector<std::string> files;
	char filename[128];

	directoryContents("data/game/weapons", &files);
	for (unsigned int i = 0; i < files.size(); i++) {
		snprintf(filename, sizeof(filename), "data/game/weapons/%s", files[i].c_str());
		loadWeapon(filename);
	}
}

//======================================================================


void fired::Container::loadWeapon(const char* filename) {
	char type[16];
	char file[128];
	char path[128];
	weapons.push_back(new fired::BaseWeapon);

	FILE *fp = fopen(filename, "r");
	fscanf(fp, "name=%s\n"      , weapons.back()->name);
	fscanf(fp, "model=%s\n"     , weapons.back()->model);
	fscanf(fp, "damage=%u\n"    , &weapons.back()->damage);
	fscanf(fp, "range=%f\n"     , &weapons.back()->range);
	fscanf(fp, "cooldown=%f\n"  , &weapons.back()->cooldown);
	fscanf(fp, "knockback=%f\n" , &weapons.back()->knockback);
	fscanf(fp, "auto=%u\n"      , &weapons.back()->automatic);
	fscanf(fp, "type=%s\n"      , type);

	if (!strcmp(type, "melee")) {
		weapons.back()->type = WEAPON_TYPE_MELEE;
		weapons.back()->clip = -1;
	} else if (!strcmp(type, "broad")) {
		weapons.back()->type = WEAPON_TYPE_BROAD;
		weapons.back()->clip = -1;
	} else if (!strcmp(type, "ranged")) {
		weapons.back()->type = WEAPON_TYPE_RANGED;
		fscanf(fp, "speed=%f\n"     , &weapons.back()->speed);
		fscanf(fp, "reload=%f\n"    , &weapons.back()->reload);
		fscanf(fp, "clip=%u\n"      , &weapons.back()->clip);

		fscanf(fp, "fire_snd=%s\n"  , file);
		snprintf(path, sizeof(path), "data/snd/weapons/%s", file);
		weapons.back()->shotBuffer = new sf::SoundBuffer();
		weapons.back()->shotBuffer->loadFromFile(path);

		fscanf(fp, "reload_snd=%s\n", file);
		snprintf(path, sizeof(path), "data/snd/weapons/%s", file);
		weapons.back()->reloadBuffer = new sf::SoundBuffer();
		weapons.back()->reloadBuffer->loadFromFile(path);

		fscanf(fp, "sprite=%s\n", path);
		if (!strcmp(path, "null")) weapons.back()->shotSprite = NULL;
		else weapons.back()->shotSprite = getBodypart(path, bptShot)->sprite;
	}

	fclose(fp);
}

//======================================================================


fired::BaseWeapon* fired::Container::getWeapon(const char* name) {
	for (unsigned int i = 0; i < weapons.size(); i++)
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
	loadBodypartsInDir("shot"  , bptShot);
	loadBodypartsInDir("weapon", bptWeapon);
}

//======================================================================


void fired::Container::loadBodypartsInDir(const char *dir, fired::BodypartType type) {
	std::vector<std::string> files;
	char dirname[128];
	char filename[128];

	bodyparts.push_back(new fired::BaseBodypart);
	bodyparts.back()->texture = new sf::Texture;
	bodyparts.back()->type = type;
	bodyparts.back()->offset = sf::Vector2f(0, 0);
	bodyparts.back()->color = sf::Color(0, 0, 0, 0);
	bodyparts.back()->sprite = new sf::Sprite;
	bodyparts.back()->chunk = new sf::Sprite;
	strncpy(bodyparts.back()->name, "null", 5);


	snprintf(dirname, sizeof(dirname), "data/game/bodyparts/%s", dir);
	directoryContents(dirname, &files);
	for (unsigned int i = 0; i < files.size(); i++) {
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
	fscanf(fp, "origin=%f,%f\n", &bodyparts.back()->origin.x, &bodyparts.back()->origin.y);
	fscanf(fp, "color=%hhu,%hhu,%hhu,%hhu\n", &bodyparts.back()->color.r, &bodyparts.back()->color.g, &bodyparts.back()->color.b, &bodyparts.back()->color.a);
	fscanf(fp, "image=%s\n"    , imgfile);
	fclose(fp);

	snprintf(imgpath, sizeof(imgpath), "data/img/world/models/%s/%s", dir, imgfile);
	bodyparts.back()->texture = new sf::Texture;
	bodyparts.back()->texture->loadFromFile(imgpath);
	bodyparts.back()->texture->setSmooth(true);

	bodyparts.back()->type = type;
	bodyparts.back()->size = sf::Vector2f(bodyparts.back()->texture->getSize());

	bodyparts.back()->sprite = new sf::Sprite;
	bodyparts.back()->sprite->setTexture(*bodyparts.back()->texture);
	bodyparts.back()->sprite->setOrigin(bodyparts.back()->origin);

	bodyparts.back()->chunk = new sf::Sprite;
	bodyparts.back()->chunk->setTexture(*bodyparts.back()->texture);
	bodyparts.back()->chunk->setOrigin(bodyparts.back()->size / 2.0f);
}

//======================================================================


fired::BaseBodypart* fired::Container::getBodypart(const char* name, fired::BodypartType type) {
	for (unsigned int i = 0; i < bodyparts.size(); i++)
		if (!strcmp(name, bodyparts[i]->name) && type == bodyparts[i]->type) return bodyparts[i];

	return NULL;
}

//======================================================================


void fired::Container::loadModels() {
	std::vector<std::string> files;
	char filename[128];

	directoryContents("data/game/models", &files);
	for (unsigned int i = 0; i < files.size(); i++) {
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

		models.push_back(model);
	}
}

//======================================================================


fired::BaseModel* fired::Container::getModel(const char* name) {
	for (unsigned int i = 0; i < models.size(); i++)
		if (!strcmp(name, models[i]->name)) return models[i];

	return NULL;
}

//======================================================================


void fired::Container::loadCreatures() {
	std::vector<std::string> files;
	char filename[128];

	directoryContents("data/game/creatures", &files);
	for (unsigned int i = 0; i < files.size(); i++) {
		snprintf(filename, sizeof(filename), "data/game/creatures/%s", files[i].c_str());
		loadCreature(filename);
	}
}

//======================================================================


void fired::Container::loadCreature(const char* filename) {
	creatures.push_back(new fired::BaseCreature);

	FILE *fp = fopen(filename, "r");
	fscanf(fp, "name=%s\n"    ,  creatures.back()->name);
	fscanf(fp, "ai=%s\n"      ,  creatures.back()->ai);
	fscanf(fp, "fraction=%s\n",  creatures.back()->fraction);
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
	for (unsigned int i = 0; i < creatures.size(); i++)
		if (!strcmp(name, creatures[i]->name)) return creatures[i];

	return NULL;
}

//======================================================================


fired::BaseAI *fired::Container::getAI(const char *name, fired::Creature *owner) {
	if (!strcmp(name, "idle")) return new fired::IdleAI(owner, world);
	if (!strcmp(name, "basic")) return new fired::BasicAI(owner, world);

	return new fired::BaseAI();
}

//======================================================================


void fired::Container::loadDecors() {
	std::vector<std::string> files;
	char filename[128];

	directoryContents("data/game/decors", &files);
	for (unsigned int i = 0; i < files.size(); i++) {
		snprintf(filename, sizeof(filename), "data/game/decors/%s", files[i].c_str());
		loadDecor(filename);
	}
}

//======================================================================


void fired::Container::loadDecor(const char* filename) {
	char name[16];
	char imgf[32];
	char img[128];

	FILE *fp = fopen(filename, "r");
	fscanf(fp, "name=%s\n"  , name);
	fscanf(fp, "sprite=%s\n", imgf);

	snprintf(img, sizeof(img), "data/img/world/decors/%s", imgf);
	decors.push_back(new fired::BaseDecor(name, img));

	fscanf(fp, "size=%f,%f\n", &decors.back()->size.x, &decors.back()->size.y);
	fclose(fp);
}

//======================================================================


fired::BaseDecor* fired::Container::getDecor(const char* name) {
	for (unsigned int i = 0; i < decors.size(); i++)
		if (!strcmp(name, decors[i]->name)) return decors[i];

	return NULL;
}

