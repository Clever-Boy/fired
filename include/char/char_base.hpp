/***********************************************************************
     * File       : char_base.hpp
     * Created    : Jul 25, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CHAR_BASE
#define __CHAR_BASE


namespace fired {
	struct Character;
}


#include "char_stats.hpp"
#include "phys.hpp"
#include "model.hpp"
#include "item.hpp"
#include "win.hpp"


namespace fired {
	struct Character {
		fired::World     *world;
		fired::Camera    *cam;

		fired::CharacterStats  baseStats;
		fired::BaseWeapon     *weapon;
		fired::BaseAmmo       *ammo;
		fired::Model          *model;
		fired::Inventory      *inventory;
		fired::BaseCreature   *base;

		fired::BaseArmor *helm;
		fired::BaseArmor *legs;
		fired::BaseArmor *arms;
		fired::BaseArmor *body;
		fired::BaseArmor *shoe;
		fired::BaseArmor *fist;

		bool  dead;
		bool  isShooting;
		bool  wasShot;
		int   direction;
		int   watching;
		float aiming;
		float weaponCooldown;
		int   fraction;

		int  level;
		long XP;
		long needXP;
		long lastXP;

		fired::Phys phys;


		 Character(fired::Camera *_cam, sf::Vector2f _startpos, fired::World *_world, fired::BaseCreature *_base);
		~Character();

		void update();
		void render();
		void respawn(sf::Vector2f pos);
		void reduceAmmo();
		bool findAmmo();

		void move();
		void moveLeft();
		void moveRight();
		void jump();
		void jumpdown();
		void shot();
		void interact();
		void swapWeapons();
		void unshot();

		bool  checkShot(fired::Shot *shot);
		void  checkMeleeShot(fired::MeleeShot *shot);
		void  checkBroadShot(fired::BroadShot *shot);

		void  damage(int damage, sf::Vector2f shot, float knockback, fired::Character *owner);
		void  gainXP(long xp);
		void  levelUp();
		void  setAiming(float _aiming);
		void  setWeapon(fired::BaseWeapon *_weapon);

		int   getArmor();
		int   getDamage();
		float getRange();
		bool  isEnemy(int _fraction);
		float getKnockback();
		void  updateEquip();

		void pickup(fired::InventoryItem *item)                  {inventory->pickup(item); };
		bool canPickup(fired::InventoryItem *item)               {return inventory->canPickup(item); };
		void generateLoot(std::vector<fired::LootItem*> *_items) {inventory->generateLoot(_items); };
	};
}

#endif
