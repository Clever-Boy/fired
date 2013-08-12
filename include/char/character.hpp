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


#define FIRED_FRACTION_PLAYER  1
#define FIRED_FRACTION_SOLDIER 2


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
		bool  isShooting;
		bool  isReloading;
		int   direction;
		int   watching;
		float aiming;
		float weaponCooldown;
		int   fraction;

		int  level;
		long XP;
		long needXP;
		long lastXP;

	public:
		fired::Phys phys;
		fired::CharacterStats *getStats() { return &baseStats; };


		 Character(fired::Game *_game, fired::Camera *_cam, sf::Vector2f _startpos, fired::World *_world, fired::BaseCreature *base);
		~Character();

		void update();
		void render();
		void respawn(sf::Vector2f pos);


		void move();
		void moveLeft();
		void moveRight();
		void jump();
		void reload();
		void shot();
		void unshot() {weapon->wasShot = false; };

		bool  checkShot(fired::Shot *shot);
		void  damage(int damage, bool headshot, sf::Vector2f shot, float knockback);
		void  gainXP(long xp);
		void  levelUp();
		void  setAiming(float _aiming);

		float getHpPercent();
		float getXpPercent();
		float getCooldownPercent();
		float getAmmoPercent();

		std::string getHpString();
		std::string getXpString();
		std::string getCooldownString();
		std::string getAmmoString();

		int   getDamage();
		int   getFraction() {return fraction; };
		bool  isEnemy(int _fraction);
		float getKnockback();
		bool  isDead()   {return dead; };
	};
}

#endif
