#ifndef __CHARACTER
#define __CHARACTER


#define ROTTEN_TIME 5.0


#include <SFML/Graphics.hpp>
#include <string>
#include "prototypes.hpp"
#include "stats.hpp"
#include "phys.hpp"
#include "model.hpp"
#include "theworld.hpp"


namespace fired {
	class Character {
		friend class Model;
		friend class ModelHumanoid;


	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;
		fired::World     *world;
		fired::Camera    *cam;

		fired::CharacterStats  baseStats;
		fired::Weapon         *weapon;
		fired::Model          *model;

		bool  dead;
		float timeAfterDeath;
		bool  isShooting;
		int   direction;
		int   watching;
		float aiming;

		int level;
		float weaponCooldown;


	public:
		fired::Phys phys;
		fired::CharacterStats *getStats() { return &baseStats; };


		 Character(fired::Game *_game, fired::Camera *_cam, sf::Vector2f _startpos, fired::World *_world, fired::BaseCreature *base);
		~Character();

		void update();
		void render();


		void move();
		void moveLeft();
		void moveRight();
		void jump();
		void shot();

		bool  checkShot(fired::Shot *shot);
		void  damage(int damage, bool headshot, sf::Vector2f shot, float knockback);
		void  setAiming(float _aiming);

		float getHpPercent();
		float getCooldownPercent();
		float getAmmoPercent();

		std::string getHpString();
		std::string getCooldownString();
		std::string getAmmoString();

		int   getDamage();
		float getKnockback();
		bool  isDead()   {return dead; };
	};
}

#endif
