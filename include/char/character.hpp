#ifndef __CHARACTER
#define __CHARACTER


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "stats.hpp"
#include "phys.hpp"
#include "model.hpp"
#include "theworld.hpp"


namespace fired {
	class Character {
		friend class Model;


	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;
		fired::World     *world;
		fired::Camera    *cam;

		fired::CharacterStats baseStats;
		fired::Weapon         weapon;
		fired::Model          model;

		bool  isShooting;
		int   direction;
		int   watching;
		float aiming;

		float weaponCooldown;


	public:
		fired::Phys phys;
		fired::CharacterStats *getStats() { return &baseStats; };


		void init(fired::Game *_game, fired::Camera *_cam, sf::Vector2f _startpos, fired::World *_world);
		void deinit();
		void update();
		void render();


		void move();
		void moveLeft();
		void moveRight();
		void jump();
		void shot();

		bool  checkShot(fired::Shot *shot);
		void  damage(int damage, bool headshot);
		void  setAiming(float _aiming);
		float getHpPercent();
		int   getAmmo() {return weapon.ammo; };
		int   getDamage();
	};
}

#endif
