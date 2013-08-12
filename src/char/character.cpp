#include "game.hpp"

//======================================================================


fired::Character::Character(fired::Game *_game, fired::Camera *_cam, sf::Vector2f _startpos, fired::World *_world, fired::BaseCreature *base) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	world    = _world;
	cam      = _cam;

	baseStats.speed    = base->stats.speed;
	baseStats.accel    = base->stats.accel;
	baseStats.jump     = base->stats.jump;
	baseStats.aimrange = base->stats.aimrange;
	baseStats.maxHP    = base->stats.maxHP;

	fired::BaseModel *basemodel = world->getModel(base->model);
	switch (basemodel->type) {
		case mtHumanoid: {
			model = new fired::ModelHumanoid(game, this, (fired::BaseModelHumanoid*)basemodel, base->modelScale, world);
			break;
		}
	}

	if (!strcmp(base->fraction, "player"))  fraction = FIRED_FRACTION_PLAYER;
	if (!strcmp(base->fraction, "soldier")) fraction = FIRED_FRACTION_SOLDIER;


	respawn(_startpos);
	weapon = new fired::Weapon(world->getWeapon(base->weapon));

	level          = 1;
	XP             = 0;
	lastXP         = 0;
	needXP         = levelXP(level);
}

//======================================================================


fired::Character::~Character() {
	delete model;
	delete weapon;
}

//======================================================================


void fired::Character::respawn(sf::Vector2f pos) {
	phys.pos          = pos;
	phys.velocity     = sf::Vector2f(0, 0);
	phys.acceleration = sf::Vector2f(0, PHYS_GRAVITY);
	phys.onGround     = false;
	phys.isMoving     = false;
	isShooting        = false;
	phys.calculate();

	baseStats.HP   = baseStats.maxHP;
	weaponCooldown = 0;
	dead           = false;
	isShooting     = false;
	direction      = 1;
	watching       = 1;
	aiming         = 0;

	model->respawn();
}

//======================================================================


void fired::Character::update() {
	move();
	world->checkPhys(this);

	model->update();
	if (phys.rect.intersects(cam->getViewport())) model->render();


	weaponCooldown -= frameClock;
	if (isReloading && weaponCooldown <= 0) {
		isReloading = false;
		weapon->ammo = weapon->clip;
	}

	phys.isMoving = false;
	isShooting    = false;
}

//======================================================================


void fired::Character::move() {
	if (abs(phys.velocity.x) < PHYS_EPSILON) phys.velocity.x = 0.0f;

	if (phys.isMoving && abs(phys.velocity.x) < baseStats.speed)
		phys.velocity.x += direction * frameClock * baseStats.accel;
	else if (frameClock * PHYS_FRICTION_ACCEL > abs(phys.velocity.x))
		phys.velocity.x = 0.0f;
	else
		phys.velocity.x -= sign(phys.velocity.x) * frameClock * PHYS_FRICTION_ACCEL;

	if (phys.velocity.x == 0.0f) phys.isMoving = false;
}

//======================================================================


void fired::Character::setAiming(float _aiming) {
	aiming = _aiming;
	if (cos(aiming) < 0) watching = -1;
	else                 watching =  1;
}

//======================================================================


void fired::Character::damage(int damage, bool headshot, sf::Vector2f shot, float knockback) {
	char dmg[8];

	baseStats.HP -= damage;
	if (baseStats.HP <= 0) {
		dead = true;
		if (headshot) model->headshot();
		model->explode(shot - phys.pos, knockback);
	}

	snprintf(dmg, sizeof(dmg), "-%u", damage);

	if (headshot)
		world->addText(phys.pos, sf::Color(255, 0, 0, 255), 24, dmg);
	else
		world->addText(phys.pos, sf::Color(255, 0, 0, 255), 16, dmg);
}

//======================================================================


void fired::Character::gainXP(long xp) {
	char exp[8];
	snprintf(exp, sizeof(exp), "+%lu XP", xp);

	XP += xp;
	world->addText(phys.pos, sf::Color(0, 255, 0, 255), 16, exp);
	if (XP >= needXP) levelUp();
}

//======================================================================


void fired::Character::levelUp() {
	lastXP = needXP;
	level++;
	world->addText(sf::Vector2f(phys.pos.x, phys.pos.y - 20), sf::Color(255, 255, 0, 255), 24, "Level UP");
	needXP = levelXP(level);
}

//======================================================================


bool fired::Character::isEnemy(int _fraction) {
	if (fraction != _fraction) return true;
	return false;
}

//======================================================================


bool fired::Character::checkShot(fired::Shot *shot) {
	if (dead) return false;
	if (!isEnemy(shot->owner->getFraction())) return false;

	sf::Vector2f  dir(shot->velocity * frameClock);
	sf::FloatRect ray(shot->pos, dir);

	sf::Vector2f c, n, c2, n2;
	float dist;

	if (lineBoxCollision(phys.rect, ray, &c, &n, &dist)) {

		if (lineBoxCollision(phys.head, ray, &c2, &n2, &dist)) {
			phys.velocity.x -= n.x * shot->knockback * 1.5;
			world->addBloodSplash(c, n * 200.0f, 30);
			damage(shot->damage * 1.5, true, c, shot->knockback * 1.5);
		} else {
			phys.velocity.x -= n.x * shot->knockback;
			world->addBloodSplash(c, n * 200.0f, 20);
			damage(shot->damage, false, c, shot->knockback);
		}

		if (dead) shot->owner->gainXP(baseStats.maxHP);
		return true;
	}


	return false;
}

//======================================================================


float fired::Character::getHpPercent() {
	if (baseStats.HP > 0) return (float)baseStats.HP / (float)baseStats.maxHP;
	return 0.0f;
}

//======================================================================


std::string fired::Character::getHpString() {
	char outStr[32];
	snprintf(outStr, sizeof(outStr), "HP  %d / %d", baseStats.HP, baseStats.maxHP);
	return std::string(outStr);
}

//======================================================================


float fired::Character::getXpPercent() {
	return (float)(XP - lastXP) / (float)(needXP - lastXP);
}

//======================================================================


std::string fired::Character::getXpString() {
	char outStr[32];
	snprintf(outStr, sizeof(outStr), "Level %u  (%lu / %lu)", level, XP, needXP);
	return std::string(outStr);
}

//======================================================================


float fired::Character::getCooldownPercent() {
	if (weaponCooldown > 0) {
		if (isReloading) return (float)(weapon->reload   - weaponCooldown) / (float)weapon->reload;
		else             return (float)(weapon->cooldown - weaponCooldown) / (float)weapon->cooldown;
	}

	return 1.0f;
}

//======================================================================


std::string fired::Character::getCooldownString() {
	char outStr[16];
	if (weaponCooldown > 0) snprintf(outStr, sizeof(outStr), "%3.2f", weaponCooldown);
	return std::string(outStr);
}

//======================================================================


float fired::Character::getAmmoPercent() {
	if (weapon->ammo >= 0) return (float)weapon->ammo / (float)weapon->clip;
	return 1.0f;
}

//======================================================================


std::string fired::Character::getAmmoString() {
	char outStr[16];
	if (weapon->ammo == -1) snprintf(outStr, sizeof(outStr), "inf");
	else                    snprintf(outStr, sizeof(outStr), "Ammo  %d / %d", weapon->ammo, weapon->clip);
	return std::string(outStr);
}

//======================================================================


int fired::Character::getDamage() {
	return weapon->damage;
}

//======================================================================


float fired::Character::getKnockback() {
	return weapon->knockback;
}

//======================================================================


void fired::Character::moveLeft() {
	direction = -1;
	phys.isMoving  = true;
}

//======================================================================


void fired::Character::moveRight() {
	direction = 1;
	phys.isMoving  = true;
}

//======================================================================


void fired::Character::jump() {
	if (phys.onGround) phys.velocity.y = -baseStats.jump;
}

//======================================================================


void fired::Character::reload() {
	if (weapon->ammo == weapon->clip) return;
	weapon->reloadSound->play();
	weaponCooldown = weapon->reload;
	isReloading = true;
}

//======================================================================


void fired::Character::shot() {
	isShooting = true;

	if (weaponCooldown > 0) return;
	if (!weapon->automatic && weapon->wasShot) return;
	if (weapon->ammo > 0) weapon->ammo--;

	weaponCooldown = weapon->cooldown;
	weapon->shotSound->play();
	weapon->wasShot = true;
	world->addShot(phys.center, aiming, 1000, this);

	if (weapon->ammo == 0) reload();
}
