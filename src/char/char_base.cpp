/***********************************************************************
     * File       : char_base.cpp
     * Created    : Jul 25, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Character
     * constructor

***********************************************************************/
fired::Character::Character(fired::Camera *_cam, sf::Vector2f _startpos, fired::World *_world, fired::BaseCreature *_base) {
	world    = _world;
	cam      = _cam;
	base     = _base;

	memcpy(&baseStats, &(base->stats), sizeof(fired::CharacterStats));
	inventory = new fired::Inventory(this);

	helm   = NULL;
	arms   = NULL;
	legs   = NULL;
	body   = NULL;
	shoe   = NULL;
	fist   = NULL;
	weapon = NULL;


	switch (_base->model->type) {
		case mtHumanoid: {
			model = new fired::ModelHumanoid(this, (fired::BaseModelHumanoid*)_base->model, base->modelScale, world);
			break;
		}
	}

	fraction = _base->fraction;

	respawn(_startpos);
	updateEquip();

	level          = 1;
	XP             = 0;
	lastXP         = 0;
	needXP         = levelXP(level);
}



/***********************************************************************
     * Character
     * destructor

***********************************************************************/
fired::Character::~Character() {
	delete model;
	delete inventory;
}



/***********************************************************************
     * Character
     * respawn

***********************************************************************/
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



/***********************************************************************
     * Character
     * update

***********************************************************************/
void fired::Character::update() {
	move();

	model->update();
	if (world->isRectVisible(phys.rect)) model->render();

	weaponCooldown -= frameClock;

	phys.isMoving = false;
	isShooting    = false;
}



/***********************************************************************
     * Character
     * move

***********************************************************************/
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



/***********************************************************************
     * Character
     * setAiming

***********************************************************************/
void fired::Character::setAiming(float _aiming) {
	aiming = _aiming;
	if (cos(aiming) < 0) watching = -1;
	else                 watching =  1;
}



/***********************************************************************
     * Character
     * setWeapon

***********************************************************************/
void fired::Character::setWeapon(fired::BaseWeapon *_weapon) {
	weapon = _weapon;
	model->setWeapon(_weapon);
}



/***********************************************************************
     * Character
     * damage

***********************************************************************/
void fired::Character::damage(int damage, sf::Vector2f shot, float knockback, fired::Character *owner) {
	char dmg[8];
	int taken = damage * (1.0f - armorReduction(getArmor()));

	if (taken <= 0) return;

	baseStats.HP -= taken;
	if (baseStats.HP <= 0) {
		dead = true;
		model->explode(shot - phys.pos, knockback);
		inventory->dropAll(world);

		if (owner) if (world->isCharExists(owner)) owner->gainXP(baseStats.maxHP);
	}

	snprintf(dmg, sizeof(dmg), "-%u", taken);
	world->addText(phys.pos, sf::Color(255, 0, 0, 255), 16, dmg);
}



/***********************************************************************
     * Character
     * gainXP

***********************************************************************/
void fired::Character::gainXP(long xp) {
	char exp[64];
	snprintf(exp, sizeof(exp), "+%lu XP", xp);

	XP += xp;
	world->addText(phys.pos, sf::Color(0, 255, 0, 255), 16, exp);
	if (XP >= needXP) levelUp();
}



/***********************************************************************
     * Character
     * levelUp

***********************************************************************/
void fired::Character::levelUp() {
	lastXP = needXP;
	level++;
	world->addText(sf::Vector2f(phys.pos.x, phys.pos.y - 20), sf::Color(255, 255, 0, 255), 24, "Level UP");
	needXP = levelXP(level);
}



/***********************************************************************
     * Character
     * isEnemy

***********************************************************************/
bool fired::Character::isEnemy(int _fraction) {
	if (fraction != _fraction) return true;
	return false;
}



/***********************************************************************
     * Character
     * checkShot

***********************************************************************/
bool fired::Character::checkShot(fired::Shot *shot) {
	if (dead) return false;

	sf::Vector2f  dir(shot->velocity * frameClock);
	sf::FloatRect ray(shot->pos, dir);

	sf::Vector2f c, n, c2, n2;
	float dist;

	if (lineBoxCollision(phys.rect, ray, &c, &n, &dist)) {
		if (!isEnemy(shot->fraction)) return false;

		if (shot->explosive) {
			world->addExplosion(c, shot->explosionRadius, 0.5f, shot->knockback, shot->damage, shot->owner, shot->fraction);
		} else {
			phys.velocity.x -= n.x * shot->knockback;
			world->addBloodSplash(c, n * 200.0f, 20);
			damage(shot->damage, c, shot->knockback, shot->owner);
		}

		return true;
	}


	return false;
}



/***********************************************************************
     * Character
     * checkBroadShot

***********************************************************************/
void fired::Character::checkBroadShot(fired::BroadShot *shot) {
	if (dead) return;
	sf::Vector2f c;

	if (phys.rect.intersects(shot->shot)) {
		if (!isEnemy(shot->fraction)) return;

		c = rectCenter(phys.rect);
		c.x += shot->normal.x * phys.size.x / 2.0f;

		phys.velocity -= shot->normal * shot->knockback;
		world->addBloodSplash(c, shot->normal * 200.0f, 20);
		damage(shot->damage, c, shot->knockback, shot->owner);

		if (world->isCharExists(shot->owner)) if (dead) shot->owner->gainXP(baseStats.maxHP);
	}
}



/***********************************************************************
     * Character
     * checkMeleeShot

***********************************************************************/
void fired::Character::checkMeleeShot(fired::MeleeShot *shot) {
	if (dead) return;

	sf::FloatRect ray(shot->pos, shot->direction);
	sf::Vector2f c, n, c2, n2;
	float dist;

	if (lineBoxCollision(phys.rect, ray, &c, &n, &dist)) {
		if (!isEnemy(shot->fraction)) return;

		phys.velocity += vNorm(shot->direction) * shot->knockback;
		world->addBloodSplash(c, n * 200.0f, 20);
		damage(shot->damage, c, shot->knockback, shot->owner);

		if (world->isCharExists(shot->owner)) if (dead) shot->owner->gainXP(baseStats.maxHP);
	}
}



/***********************************************************************
     * Character
     * getHpPercent

***********************************************************************/
float fired::Character::getHpPercent() {
	if (baseStats.HP > 0) return (float)baseStats.HP / (float)baseStats.maxHP;
	return 0.0f;
}



/***********************************************************************
     * Character
     * getHpString

***********************************************************************/
std::string fired::Character::getHpString() {
	char outStr[64];
	snprintf(outStr, sizeof(outStr), "HP  %d / %d", baseStats.HP, baseStats.maxHP);
	return std::string(outStr);
}



/***********************************************************************
     * Character
     * getXpPercent

***********************************************************************/
float fired::Character::getXpPercent() {
	return (float)(XP - lastXP) / (float)(needXP - lastXP);
}



/***********************************************************************
     * Character
     * getXpString

***********************************************************************/
std::string fired::Character::getXpString() {
	char outStr[64];
	snprintf(outStr, sizeof(outStr), "Level %u  (%lu / %lu)", level, XP, needXP);
	return std::string(outStr);
}



/***********************************************************************
     * Character
     * getCooldownPercent

*********************************************************************/
float fired::Character::getCooldownPercent() {
	if (weaponCooldown > 0)
		return (float)(weapon->cooldown - weaponCooldown) / (float)weapon->cooldown;

	return 1.0f;
}



/***********************************************************************
     * Character
     * getCooldownString

***********************************************************************/
std::string fired::Character::getCooldownString() {
	char outStr[16];
	if (weaponCooldown > 0) snprintf(outStr, sizeof(outStr), "%3.2f", weaponCooldown);
	return std::string(outStr);
}



/***********************************************************************
     * Character
     * getAmmoPercent

***********************************************************************/
float fired::Character::getAmmoPercent() {
	return 1.0f;
}



/***********************************************************************
     * Character
     * getAmmoString

***********************************************************************/
std::string fired::Character::getAmmoString() {
	return std::string("inf");
}



/***********************************************************************
     * Character
     * getDamage

***********************************************************************/
int fired::Character::getDamage() {
	return weapon->damage;
}



/***********************************************************************
     * Character
     * getArmor

***********************************************************************/
int fired::Character::getArmor() {
	return baseStats.armor;
}



/***********************************************************************
     * Character
     * getRange

***********************************************************************/
float fired::Character::getRange() {
	return weapon->range;
}



/***********************************************************************
     * Character
     * getKnockback

***********************************************************************/
float fired::Character::getKnockback() {
	return weapon->knockback;
}



/***********************************************************************
     * Character
     * moveLeft

***********************************************************************/
void fired::Character::moveLeft() {
	direction = -1;
	phys.isMoving  = true;
}



/***********************************************************************
     * Character
     * moveRight

***********************************************************************/
void fired::Character::moveRight() {
	direction = 1;
	phys.isMoving  = true;
}



/***********************************************************************
     * Character
     * jump

***********************************************************************/
void fired::Character::jump() {
	if (phys.onGround) phys.velocity.y = -baseStats.jump;
}



/***********************************************************************
     * Character
     * jumpdown

***********************************************************************/
void fired::Character::jumpdown() {
	phys.jumpdown = true;
}



/***********************************************************************
     * Character
     * interact

***********************************************************************/
void fired::Character::interact() {
	world->interact(this);
}



/***********************************************************************
     * Character
     * swapWeapons

***********************************************************************/
void fired::Character::swapWeapons() {
	if (weaponCooldown > 0) return;
	swapItems(&inventory->primaryWeapon, &inventory->secondaryWeapon);

	if (inventory->primaryWeapon.base) setWeapon(container->weapons[inventory->primaryWeapon.base->UID]);
	else                               setWeapon(base->weapon);

	weaponCooldown = weapon->cooldown;
}



/***********************************************************************
     * Character
     * updateEquip

***********************************************************************/
void fired::Character::updateEquip() {
	baseStats.armor = 0;

	if (helm) helm = NULL;
	if (arms) arms = NULL;
	if (legs) legs = NULL;
	if (body) body = NULL;
	if (shoe) shoe = NULL;
	if (fist) fist = NULL;


	if (inventory->helm.base) {
		helm = container->armors[inventory->helm.base->UID];
		baseStats.armor += helm->armor;
	}

	if (inventory->body.base) {
		body = container->armors[inventory->body.base->UID];
		baseStats.armor += body->armor;
	}

	if (inventory->arms.base) {
		arms = container->armors[inventory->arms.base->UID];
		baseStats.armor += arms->armor;
	}

	if (inventory->fist.base) {
		fist = container->armors[inventory->fist.base->UID];
		baseStats.armor += fist->armor;
	}

	if (inventory->legs.base) {
		legs = container->armors[inventory->legs.base->UID];
		baseStats.armor += legs->armor;
	}

	if (inventory->shoe.base) {
		shoe = container->armors[inventory->shoe.base->UID];
		baseStats.armor += shoe->armor;
	}

	if (inventory->primaryWeapon.base) setWeapon(container->weapons[inventory->primaryWeapon.base->UID]);
	else                               setWeapon(base->weapon);

	model->updateParts();
}



/***********************************************************************
     * Character
     * shot

***********************************************************************/
void fired::Character::shot() {
	if (weaponCooldown > 0) {
		if (weapon->type == WEAPON_TYPE_RANGED) isShooting = true;
		return;
	}

	isShooting = true;
	if (weaponCooldown > 0) return;
	if (!weapon->automatic && wasShot) return;

	weaponCooldown = weapon->cooldown;
	wasShot = true;

	if (weapon->shotSound) weapon->shotSound->play();

	if (weapon->type == WEAPON_TYPE_RANGED)     world->addShot(this);
	else if (weapon->type == WEAPON_TYPE_MELEE) world->addMeleeShot(rectCenter(phys.rect), sf::Vector2f(cos(aiming) * weapon->range, sin(aiming) * weapon->range), this);
	else if (weapon->type == WEAPON_TYPE_BROAD) {
		if (watching == 1)
			world->addBroadShot(sf::FloatRect(phys.pos.x + phys.size.x / 2, phys.pos.y - weapon->range, phys.size.x / 2 + weapon->range, phys.size.y + weapon->range * 2), sf::Vector2f(-watching, 0), this);
		else
			world->addBroadShot(sf::FloatRect(phys.pos.x - weapon->range, phys.pos.y - weapon->range, phys.size.x / 2 + weapon->range, phys.size.y + weapon->range * 2), sf::Vector2f(-watching, 0), this);
	}
}



/***********************************************************************
     * Character
     * unshot

***********************************************************************/
void fired::Character::unshot() {
	wasShot = false;
}
