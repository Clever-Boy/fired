#include "game.hpp"

//======================================================================


fired::Container::Container(fired::World *_world) {
	world    = _world;

	loadSprites();
	loadBodyparts();
	loadWeapons();
	loadArmors();
	loadModels();
	loadCreatures();
	loadDecors();

	NewLoad();
}

//======================================================================


fired::Container::~Container() {
	deleteList(weapons);
	deleteList(armors);
	deleteList(bodyparts);
	deleteList(models);
	deleteList(creatures);
	deleteList(decors);
	deleteList(sprites);

	deleteList(_sprites);
	deleteList(_bodyparts);
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
	char type[64];
	char file[128];
	char path[128];
	weapons.push_back(new fired::BaseWeapon);

	FILE *fp = fopen(filename, "r");
	fscanf(fp, "name=%s\n"       , weapons.back()->name);
	fscanf(fp, "caption=%[^\n]\n", weapons.back()->caption);
	fscanf(fp, "model=%s\n"      , weapons.back()->model);
	fscanf(fp, "damage=%u\n"     , &weapons.back()->damage);
	fscanf(fp, "range=%f\n"      , &weapons.back()->range);
	fscanf(fp, "cooldown=%f\n"   , &weapons.back()->cooldown);
	fscanf(fp, "knockback=%f\n"  , &weapons.back()->knockback);
	fscanf(fp, "auto=%u\n"       , &weapons.back()->automatic);
	fscanf(fp, "type=%s\n"       , type);

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
		else weapons.back()->shotSprite = getSprite(path);
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


void fired::Container::loadArmors() {
	loadArmorsInDir("arms" , acArms);
	loadArmorsInDir("body" , acBody);
	loadArmorsInDir("head" , acHelm);
	loadArmorsInDir("fist" , acFist);
	loadArmorsInDir("legs" , acLegs);
	loadArmorsInDir("shoe" , acShoe);
}

//======================================================================


void fired::Container::loadArmorsInDir(const char *dir, fired::ArmorClass type) {
	std::vector<std::string> files;
	char dirname[128];
	char filename[128];


	snprintf(dirname, sizeof(dirname), "data/game/armors/%s", dir);
	directoryContents(dirname, &files);
	for (unsigned int i = 0; i < files.size(); i++) {
		snprintf(filename, sizeof(filename), "data/game/armors/%s/%s", dir, files[i].c_str());
		loadArmor(filename, type);
	}
}

//======================================================================


void fired::Container::loadArmor(const char* filename, fired::ArmorClass type) {
	armors.push_back(new fired::BaseArmor);
	armors.back()->type = type;

	FILE *fp = fopen(filename, "r");
	fscanf(fp, "name=%s\n"       ,  armors.back()->name);
	fscanf(fp, "caption=%[^\n]\n",  armors.back()->caption);
	fscanf(fp, "armor=%d\n"      , &armors.back()->armor);
	fscanf(fp, "model=%s\n"      ,  armors.back()->model);
	fscanf(fp, "color=%hhu,%hhu,%hhu,%hhu\n", &armors.back()->color.r, &armors.back()->color.g, &armors.back()->color.b, &armors.back()->color.a);
	fclose(fp);
}

//======================================================================


fired::BaseArmor* fired::Container::getArmor(const char* name, fired::ArmorClass type) {
	for (unsigned int i = 0; i < armors.size(); i++)
		if (!strcmp(name, armors[i]->name) && type == armors[i]->type) return armors[i];

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

	bodyparts.push_back(new fired::BaseBodypart);
	bodyparts.back()->texture = new sf::Texture;
	bodyparts.back()->type = type;
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
	fscanf(fp, "origin=%f,%f\n", &bodyparts.back()->origin.x, &bodyparts.back()->origin.y);
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


void fired::Container::loadModelBodypart(const char* s, fired::BaseModelBodypart *bodypart, fired::BodypartType type) {
	char field[128];

	sscanf(s, "%[^,],(%hhu,%hhu,%hhu,%hhu),(%f,%f)\n", field, &bodypart->color.r, &bodypart->color.g, &bodypart->color.b, &bodypart->color.a, &bodypart->offset.x, &bodypart->offset.y);
	bodypart->part = getBodypart(field, type);
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
		fscanf(fp, "weapon_offset=%f,%f\n", &model->weaponOffset.x, &model->weaponOffset.y);

		fscanf(fp, "legsf=%s\n", field); loadModelBodypart(field, &model->partLegsF, bptLegsF);
		fscanf(fp, "legsb=%s\n", field); loadModelBodypart(field, &model->partLegsB, bptLegsB);
		fscanf(fp, "shoef=%s\n", field); loadModelBodypart(field, &model->partShoeF, bptShoeF);
		fscanf(fp, "shoeb=%s\n", field); loadModelBodypart(field, &model->partShoeB, bptShoeB);
		fscanf(fp, "fistf=%s\n", field); loadModelBodypart(field, &model->partFistF, bptFistF);
		fscanf(fp, "fistb=%s\n", field); loadModelBodypart(field, &model->partFistB, bptFistB);
		fscanf(fp, "arms=%s\n" , field); loadModelBodypart(field, &model->partArms , bptArms );
		fscanf(fp, "hair=%s\n" , field); loadModelBodypart(field, &model->partHair , bptHair );
		fscanf(fp, "head=%s\n" , field); loadModelBodypart(field, &model->partHead , bptHead );
		fscanf(fp, "body=%s\n" , field); loadModelBodypart(field, &model->partBody , bptBody );

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
	fired::ItemType type;
	char            strtype[64];
	char            name[64];
	unsigned int    minCount;
	unsigned int    maxCount;
	float           probability;


	creatures.push_back(new fired::BaseCreature);
	creatures.back()->loot.clear();

	FILE *fp = fopen(filename, "r");
	fscanf(fp, "name=%s\n"    ,  creatures.back()->name);
	fscanf(fp, "ai=%s\n"      ,  creatures.back()->ai);
	fscanf(fp, "fraction=%s\n",  creatures.back()->fraction);
	fscanf(fp, "model=%s\n"   ,  creatures.back()->model);
	fscanf(fp, "scale=%f\n"   , &creatures.back()->modelScale);
	fscanf(fp, "weapon=%s\n"  ,  creatures.back()->weapon);
	fscanf(fp, "armor=%u\n"   , &creatures.back()->stats.armor);
	fscanf(fp, "speed=%f\n"   , &creatures.back()->stats.speed);
	fscanf(fp, "accel=%f\n"   , &creatures.back()->stats.accel);
	fscanf(fp, "jump=%f\n"    , &creatures.back()->stats.jump);
	fscanf(fp, "aimrange=%f\n", &creatures.back()->stats.aimrange);
	fscanf(fp, "maxHP=%u\n"   , &creatures.back()->stats.maxHP);

	while (fscanf(fp, "loot=(%[^,],%[^)]),(%u,%u),%f\n", strtype, name, &minCount, &maxCount, &probability) != EOF) {
		if (!strcmp(strtype, "money" )) type = itMoney;
		if (!strcmp(strtype, "weapon")) type = itWeapon;
		if (!strcmp(strtype, "helm")) type = itArmorHelm;
		if (!strcmp(strtype, "fist")) type = itArmorFist;
		if (!strcmp(strtype, "legs")) type = itArmorLegs;
		if (!strcmp(strtype, "body")) type = itArmorBody;
		if (!strcmp(strtype, "arms")) type = itArmorArms;
		if (!strcmp(strtype, "shoe")) type = itArmorShoe;

		creatures.back()->loot.push_back(new fired::LootItem(type, name, minCount, maxCount, probability));
	}

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
	char name[64];
	char imgf[64];
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

//======================================================================


void fired::Container::loadSprites() {
	std::vector<std::string> files;
	char filename[128];

	directoryContents("data/game/sprites", &files);
	for (unsigned int i = 0; i < files.size(); i++) {
		snprintf(filename, sizeof(filename), "data/game/sprites/%s", files[i].c_str());
		loadSprite(filename);
	}
}

//======================================================================


void fired::Container::loadSprite(const char* filename) {
	char name[64];
	char file[128];
	char path[128];

	FILE *fp = fopen(filename, "r");
	fscanf(fp, "name=%s\n"  , name);
	fscanf(fp, "sprite=%s\n", file);
	fclose(fp);

	snprintf(path, sizeof(path), "data/img/world/sprites/%s", file);
	sprites.push_back(new fired::GameSprite(name, path));
}

//======================================================================


sf::Sprite* fired::Container::getSprite(const char* name) {
	for (unsigned int i = 0; i < sprites.size(); i++)
		if (!strcmp(name, sprites[i]->name)) return sprites[i]->spr;

	return NULL;
}

//======================================================================


void fired::Container::NewLoad() {
	// move code to constructor later
	sqlite3 *db;
	sqlite3_open("data/database.sqlite", &db);

	_loadSprites(db);
	_loadBodyparts(db);

	sqlite3_close(db);
}

//======================================================================


void fired::Container::_loadSprites(sqlite3 *db) {
	char *zErrMsg = 0;

	if (sqlite3_exec(db, "SELECT Path FROM Sprites", _loadSprite, this, &zErrMsg) != SQLITE_OK)
		printf("SQL error: %s\n", zErrMsg);
}

//======================================================================


int fired::Container::_loadSprite(void *data, int, char **argv, char **){
	((fired::Container *) data)->_sprites.push_back(new fired::NewGameSprite(argv[0]));
	return 0;
}

//======================================================================


void fired::Container::_loadBodyparts(sqlite3 *db) {
	char *zErrMsg = 0;

	if (sqlite3_exec(db, "SELECT Bodyparts.Name, Bodyparts.BodypartType, Bodyparts.Origin, Sprites.ID FROM Bodyparts, Sprites WHERE Sprites.Name = Bodyparts.Sprite", _loadBodypart, this, &zErrMsg) != SQLITE_OK)
		printf("SQL error: %s\n", zErrMsg);
}

//======================================================================


int fired::Container::_loadBodypart(void *data, int, char **argv, char **){
	((fired::Container *) data)->_bodyparts.push_back(new fired::NewBaseBodypart);
	fired::NewBaseBodypart *current = ((fired::Container *) data)->_bodyparts.back();

	strcpy(current->name, argv[0]);

	if (!strcmp(argv[1], "arms"  )) current->type = bptArms;
	if (!strcmp(argv[1], "head"  )) current->type = bptHead;
	if (!strcmp(argv[1], "hair"  )) current->type = bptHair;
	if (!strcmp(argv[1], "body"  )) current->type = bptBody;
	if (!strcmp(argv[1], "legs"  )) current->type = bptLegs;
	if (!strcmp(argv[1], "shoe"  )) current->type = bptShoe;
	if (!strcmp(argv[1], "fist"  )) current->type = bptFist;
	if (!strcmp(argv[1], "weapon")) current->type = bptWeapon;

	sscanf(argv[2], "%f,%f", &current->origin.x, &current->origin.y);
	current->sprite = ((fired::Container *) data)->_sprites[atoi(argv[3])]->spr;
	current->size   = sf::Vector2f(((fired::Container *) data)->_sprites[atoi(argv[3])]->tex->getSize());
	return 0;
}

//======================================================================


void fired::Container::_loadModels(sqlite3 *db) {
	char *zErrMsg = 0;

	if (sqlite3_exec(db, "SELECT * FROM Models", _loadModel, this, &zErrMsg) != SQLITE_OK)
		printf("SQL error: %s\n", zErrMsg);
}

//======================================================================


int fired::Container::_loadModel(void *data, int, char **argv, char **){
	if (!strcmp(argv[1], "humanoid")) {
		fired::NewBaseModelHumanoid *model = new fired::NewBaseModelHumanoid;
		model->type = mtHumanoid;

		sscanf(argv[3], "%f,%f\n", &model->size.x, &model->size.y);
		sscanf(argv[4], "%f,%f\n", &model->weaponOffset.x, &model->weaponOffset.y);
/*
		fscanf(fp, "legsf=%s\n", field); loadModelBodypart(field, &model->partLegsF, bptLegsF);
		fscanf(fp, "legsb=%s\n", field); loadModelBodypart(field, &model->partLegsB, bptLegsB);
		fscanf(fp, "shoef=%s\n", field); loadModelBodypart(field, &model->partShoeF, bptShoeF);
		fscanf(fp, "shoeb=%s\n", field); loadModelBodypart(field, &model->partShoeB, bptShoeB);
		fscanf(fp, "fistf=%s\n", field); loadModelBodypart(field, &model->partFistF, bptFistF);
		fscanf(fp, "fistb=%s\n", field); loadModelBodypart(field, &model->partFistB, bptFistB);
		fscanf(fp, "arms=%s\n" , field); loadModelBodypart(field, &model->partArms , bptArms );
		fscanf(fp, "hair=%s\n" , field); loadModelBodypart(field, &model->partHair , bptHair );
		fscanf(fp, "head=%s\n" , field); loadModelBodypart(field, &model->partHead , bptHead );
		fscanf(fp, "body=%s\n" , field); loadModelBodypart(field, &model->partBody , bptBody );
*/
		((fired::Container *) data)->_models.push_back(model);
	}

	return 0;
}
