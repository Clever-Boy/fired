#include "game.hpp"

//======================================================================


void fired::Character::init(fired::Game *_game, fired::Camera *_cam, sf::Vector2f _startpos, fired::World *_world) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	world    = _world;
	cam      = _cam;

	phys.pos          = _startpos;
	phys.velocity     = sf::Vector2f(0, 0);
	phys.acceleration = sf::Vector2f(0, PHYS_GRAVITY);
	phys.size         = sf::Vector2f(32, 48);
	phys.onGround     = false;
	phys.isMoving     = false;
	isShooting        = false;
	phys.calculate();

	baseStats.speed    = 180.0;
	baseStats.accel    = 1200.0;
	baseStats.jump     = 520.0;
	baseStats.aimrange = 100.0;
	baseStats.maxHP    = 100;
	baseStats.HP       = baseStats.maxHP;


	model.init(game, this, world->getModel("common"));
	weapon.init(world->getWeapon("rifle"));
	weapon.ammo = -1;

	weaponCooldown = 0;

	direction = 1;
	watching  = 1;
	aiming    = 0;
}

//======================================================================


void fired::Character::deinit() {
	model.deinit();
}

//======================================================================


void fired::Character::update() {
	world->checkPhys(this);
	move();
	model.update();
	if (phys.rect.intersects(cam->getViewport())) model.render();


	weaponCooldown -= frameClock;
	phys.isMoving = false;
	isShooting    = false;
}

//======================================================================


void fired::Character::move() {
	if (phys.isMoving) {
		phys.velocity.x += direction * frameClock * baseStats.accel;
		if (abs(phys.velocity.x) > baseStats.speed) phys.velocity.x = direction * baseStats.speed;
	} else
		phys.velocity.x = 0.0;
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
	snprintf(dmg, 8, "-%u", damage);

	if (headshot)
		world->addText(phys.pos, sf::Color(255, 0, 0, 255), 24, dmg);
	else
		world->addText(phys.pos, sf::Color(255, 0, 0, 255), 16, dmg);
}

//======================================================================


bool fired::Character::checkShot(fired::Shot *shot) {
	sf::Vector2f dir(shot->velocity * frameClock);
	sf::FloatRect ray(shot->pos, dir);

	sf::Vector2f c, n;
	float dist;

	if (lineBoxCollision(phys.rect, ray, &c, &n, &dist)) {
		if (lineBoxCollision(phys.head, ray, &c, &n, &dist))
			damage(shot->damage * 1.5, true);
		else
			damage(shot->damage, false);

		n *= 200.0f;
		world->addBloodSplash(c, n);
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
