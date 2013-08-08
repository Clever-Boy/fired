#include "game.hpp"

//======================================================================


void fired::Character::init(fired::Game *_game, fired::Camera *_cam, sf::Vector2f _startpos, fired::World *_world, fired::BaseCreature *base) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	world    = _world;
	cam      = _cam;

	phys.pos          = _startpos;
	phys.velocity     = sf::Vector2f(0, 0);
	phys.acceleration = sf::Vector2f(0, PHYS_GRAVITY);
	phys.onGround     = false;
	phys.isMoving     = false;
	isShooting        = false;
	phys.calculate();

	baseStats.speed    = base->stats.speed;
	baseStats.accel    = base->stats.accel;
	baseStats.jump     = base->stats.jump;
	baseStats.aimrange = base->stats.aimrange;
	baseStats.maxHP    = base->stats.maxHP;

	baseStats.HP       = baseStats.maxHP;

	fired::BaseModel *basemodel = world->getModel(base->model);
	switch (basemodel->type) {
		case mtHumanoid: {
			fired::ModelHumanoid *newmodel = new fired::ModelHumanoid;
			newmodel->init(game, this, (fired::BaseModelHumanoid*)basemodel, base->modelScale, world);
			model = newmodel;
			break;
		}
	}

	weapon.init(world->getWeapon(base->weapon));
	weapon.ammo = -1;

	weaponCooldown = 0;

	dead           = false;
	rotten         = false;
	timeAfterDeath = 0.0;
	isShooting     = false;
	direction      = 1;
	watching       = 1;
	aiming         = 0;
}

//======================================================================


void fired::Character::deinit() {
	model->deinit();
	delete model;
}

//======================================================================


void fired::Character::update() {
	world->checkPhys(this);

	if (dead) timeAfterDeath += frameClock;
	if (timeAfterDeath > ROTTEN_TIME) rotten = true;

	move();

	model->update();
	if (phys.rect.intersects(cam->getViewport())) model->render();


	weaponCooldown -= frameClock;
	phys.isMoving = false;
	isShooting    = false;
}

//======================================================================


void fired::Character::move() {
	if (dead) phys.isMoving = false;
	if (abs(phys.velocity.x) < PHYS_EPSILON) phys.velocity.x = 0.0f;

	if (phys.isMoving && abs(phys.velocity.x) < baseStats.speed)
			phys.velocity.x += direction * frameClock * baseStats.accel;
	else
			phys.velocity.x -= sign(phys.velocity.x) * frameClock * PHYS_FRICTION_ACCEL;
}

//======================================================================


void fired::Character::setAiming(float _aiming) {
	aiming = _aiming;
	if (cos(aiming) < 0) watching = -1;
	else                 watching =  1;
}

//======================================================================


void fired::Character::damage(int damage, bool headshot) {
	char dmg[8];

	baseStats.HP -= damage;
	if (baseStats.HP <= 0) dead = true;

	snprintf(dmg, 8, "-%u", damage);

	if (headshot)
		world->addText(phys.pos, sf::Color(255, 0, 0, 255), 24, dmg);
	else
		world->addText(phys.pos, sf::Color(255, 0, 0, 255), 16, dmg);
}

//======================================================================


bool fired::Character::checkShot(fired::Shot *shot) {
	if (dead) return false;

	sf::Vector2f dir(shot->velocity * frameClock);
	sf::FloatRect ray(shot->pos, dir);

	sf::Vector2f c, n;
	float dist;

	if (lineBoxCollision(phys.rect, ray, &c, &n, &dist)) {
		phys.velocity.x -= n.x * shot->knockback;
		world->addBloodSplash(c, n * 200.0f, 20);

		if (lineBoxCollision(phys.head, ray, &c, &n, &dist)) {
			damage(shot->damage * 1.5, true);
			model->headshot();
		} else
			damage(shot->damage, false);

		return true;
	}


	return false;
}

//======================================================================


float fired::Character::getHpPercent() {
	if (baseStats.HP > 0) return (float)baseStats.HP / (float)baseStats.maxHP;
	return 0.0;
}

//======================================================================


int fired::Character::getDamage() {
	return weapon.damage;
}

//======================================================================


float fired::Character::getKnockback() {
	return weapon.knockback;
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


void fired::Character::shot() {
	isShooting = true;

	if (weapon.ammo == 0) return;
	if (weaponCooldown > 0) return;
	if (weapon.ammo > 0) weapon.ammo--;

	weaponCooldown = weapon.cooldown;
	weapon.shotSound->play();
	world->addShot(phys.center, aiming, 1000, this);
}
