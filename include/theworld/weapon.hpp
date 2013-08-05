#ifndef __WEAPON
#define __WEAPON


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	class BaseWeapon {
		friend class Weapon;


	private:
		float damage;


	public:
		void init();
	};



	class Weapon {
	private:
		fired::BaseWeapon *baseWeapon;


	public:
		void init(fired::BaseWeapon *_weapon);
	};
}

#endif
