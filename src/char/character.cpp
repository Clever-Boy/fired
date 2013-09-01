#include "game.hpp"

//======================================================================


fired::Character::Character(fired::Camera *_cam, sf::Vector2f _startpos, fired::World *_world, fired::BaseCreature *_base) {
	world    = _world;
	cam      = _cam;
	base     = _base;

	baseStats.speed    = base->stats.speed;
	baseStats.accel    = base->stats.accel;
	baseStats.jump     = base->stats.jump;
	baseStats.aimrange = base->stats.aimrange;
	baseStats.maxHP    = base->stats.maxHP;
	baseStats.armor    = base->stats.armor;

	inventory = new fired::Inventory(this, world);

	helm   = NULL;
	arms   = NULL;
	legs   = NULL;
	body   = NULL;
	shoe   = NULL;
	fist   = NULL;
	weapon = NULL;


	fired::BaseModel *basemodel = world->getModel(base->model);
	switch (basemodel->type) {
		case mtHumanoid: {
			model = new fired::ModelHumanoid(this, (fired::BaseModelHumanoid*)basemodel, base->modelScale, world);
			break;
		}
	}

	if (!strcmp(base->fraction, "player"))  fraction = FIRED_FRACTION_PLAYER;
	if (!strcmp(base->fraction, "soldier")) fraction = FIRED_FRACTION_SOLDIER;

	respawn(_startpos);
	updateEquip();

	level          = 1;
	XP             = 0;
	lastXP         = 0;
	needXP         = levelXP(level);
}

//======================================================================


fired::Character::~Character() {
	delete model;
	delete weapon;
	delete inventory;

	if (helm) delete helm;
	if (arms) delete arms;
	if (legs) delete legs;
	if (body) delete body;
	if (shoe) delete shoe;
	if (fist) delete fist;
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

	model->update();
	if (world->isRectVisible(phys.rect)) model->render();

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


void fired::Character::setWeapon(fired::BaseWeapon *_weapon) {
	if (weapon) {delete weapon; weapon = NULL;}

	weapon = new fired::Weapon(_weapon);
	model->setWeapon(_weapon);
}

//======================================================================


void fired::Character::damage(int damage, bool headshot, sf::Vector2f shot, float knockback) {
	char dmg[8];
	int taken = damage * (1.0f - armorReduction(getArmor()));

	baseStats.HP -= taken;
	if (baseStats.HP <= 0) {
		dead = true;
		if (headshot) model->headshot();
		model->explode(shot - phys.pos, knockback);
		inventory->dropAll(world);
	}

	snprintf(dmg, sizeof(dmg), "-%u", taken);

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

	sf::Vector2f  dir(shot->velocity * frameClock);
	sf::FloatRect ray(shot->pos, dir);

	sf::Vector2f c, n, c2, n2;
	float dist;

	if (lineBoxCollision(phys.rect, ray, &c, &n, &dist)) {
		if (world->isCharExists(shot->owner)) if (!isEnemy(shot->owner->getFraction())) return false;

		if (lineBoxCollision(phys.head, ray, &c2, &n2, &dist)) {
			phys.velocity.x -= n.x * shot->knockback * 1.5;
			world->addBloodSplash(c, n * 200.0f, 30);
			damage(shot->damage * 1.5, true, c, shot->knockback * 1.5);
		} else {
			phys.velocity.x -= n.x * shot->knockback;
			world->addBloodSplash(c, n * 200.0f, 20);
			damage(shot->damage, false, c, shot->knockback);
		}

		if (world->isCharExists(shot->owner)) if (dead) shot->owner->gainXP(baseStats.maxHP);
		return true;
	}


	return false;
}

//======================================================================


void fired::Character::checkBroadShot(fired::BroadShot *shot) {
	if (dead) return;
	sf::Vector2f c;

	if (phys.rect.intersects(shot->shot)) {
		if (world->isCharExists(shot->owner)) if (!isEnemy(shot->owner->getFraction())) return;

		if (phys.head.intersects(shot->shot)) {
			c = rectCenter(phys.head);
			phys.velocity -= shot->normal * shot->knockback * 1.5f;
			world->addBloodSplash(c, shot->normal * 200.0f, 30);
			damage(shot->damage * 1.5, true, c, shot->knockback * 1.5f);
		} else {
			c = rectCenter(phys.rect);
			phys.velocity -= shot->normal * shot->knockback;
			world->addBloodSplash(c, shot->normal * 200.0f, 20);
			damage(shot->damage, false, c, shot->knockback);
		}

		if (world->isCharExists(shot->owner)) if (dead) shot->owner->gainXP(baseStats.maxHP);
	}
}

//======================================================================


void fired::Character::checkMeleeShot(fired::MeleeShot *shot) {
	if (dead) return;

	sf::FloatRect ray(shot->pos, shot->direction);
	sf::Vector2f c, n, c2, n2;
	float dist;

	if (lineBoxCollision(phys.rect, ray, &c, &n, &dist)) {
		if (world->isCharExists(shot->owner)) if (!isEnemy(shot->owner->getFraction())) return;

		if (lineBoxCollision(phys.head, ray, &c2, &n2, &dist)) {
			phys.velocity += vNorm(shot->direction) * shot->knockback * 1.5f;
			world->addBloodSplash(c, n * 200.0f, 30);
			damage(shot->damage * 1.5, true, c, shot->knockback * 1.5);
		} else {
			phys.velocity += vNorm(shot->direction) * shot->knockback;
			world->addBloodSplash(c, n * 200.0f, 20);
			damage(shot->damage, false, c, shot->knockback);
		}

		if (world->isCharExists(shot->owner)) if (dead) shot->owner->gainXP(baseStats.maxHP);
	}
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


int fired::Character::getArmor() {
	return baseStats.armor;
}

//======================================================================


float fired::Character::getRange() {
	return weapon->range;
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


void fired::Character::jumpdown() {
	phys.jumpdown = true;
}

//======================================================================


void fired::Character::interact() {
	world->interact(this);
}

//======================================================================


void fired::Character::updateEquip() {
	baseStats.armor = 0;

	if (helm) {delete helm; helm = NULL; }
	if (arms) {delete arms; arms = NULL; }
	if (legs) {delete legs; legs = NULL; }
	if (body) {delete body; body = NULL; }
	if (shoe) {delete shoe; shoe = NULL; }
	if (fist) {delete fist; fist = NULL; }


	if (inventory->helm) {
		helm = new fired::Armor(world->getArmor(inventory->helm->name, acHelm), world);
		baseStats.armor += helm->armor;
	}

	if (inventory->body) {
		body = new fired::Armor(world->getArmor(inventory->body->name, acBody), world);
		baseStats.armor += body->armor;
	}

	if (inventory->arms) {
		arms = new fired::Armor(world->getArmor(inventory->arms->name, acArms), world);
		baseStats.armor += arms->armor;
	}

	if (inventory->fist) {
		fist = new fired::Armor(world->getArmor(inventory->fist->name, acFist), world);
		baseStats.armor += fist->armor;
	}

	if (inventory->legs) {
		legs = new fired::Armor(world->getArmor(inventory->legs->name, acLegs), world);
		baseStats.armor += legs->armor;
	}

	if (inventory->shoe) {
		shoe = new fired::Armor(world->getArmor(inventory->shoe->name, acShoe), world);
		baseStats.armor += shoe->armor;
	}

	if (inventory->primaryWeapon) setWeapon(world->getWeapon(inventory->primaryWeapon->name));
	else                          setWeapon(world->getWeapon(base->weapon));

	model->updateParts();
}

//======================================================================


void fired::Character::reload() {
	if (weapon->ammo == weapon->clip) return;
	if (weapon->reloadSound) weapon->reloadSound->play();
	weaponCooldown = weapon->reload;
	isReloading = true;
}

//======================================================================


void fired::Character::shot() {
	if (weaponCooldown > 0) {
		if (weapon->type == WEAPON_TYPE_RANGED) isShooting = true;
		return;
	}

	isShooting = true;
	if (weaponCooldown > 0) return;
	if (!weapon->automatic && weapon->wasShot) return;
	if (weapon->ammo > 0) weapon->ammo--;

	weaponCooldown = weapon->cooldown;
	weapon->wasShot = true;

	if (weapon->shotSound) weapon->shotSound->play();

	if (weapon->type == WEAPON_TYPE_RANGED)     world->addShot(phys.center, aiming, weapon->speed, this, weapon->shotSprite);
	else if (weapon->type == WEAPON_TYPE_MELEE) world->addMeleeShot(rectCenter(phys.rect), sf::Vector2f(cos(aiming) * weapon->range, sin(aiming) * weapon->range), this);
	else if (weapon->type == WEAPON_TYPE_BROAD) {
		if (watching == 1)
			world->addBroadShot(sf::FloatRect(phys.pos.x + phys.size.x / 2, phys.pos.y - weapon->range, phys.size.x / 2 + weapon->range, phys.size.y + weapon->range * 2), sf::Vector2f(-watching, 0), this);
		else
			world->addBroadShot(sf::FloatRect(phys.pos.x - weapon->range, phys.pos.y - weapon->range, phys.size.x / 2 + weapon->range, phys.size.y + weapon->range * 2), sf::Vector2f(-watching, 0), this);
	}

	if (weapon->ammo == 0) reload();
}
