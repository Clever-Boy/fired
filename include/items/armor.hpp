#ifndef __ARMOR
#define __ARMOR


namespace fired {
	enum ArmorClass {
		acHelm,
		acBody,
		acLegs,
		acFist,
		acArms,
		acShoe
	};


	struct BaseArmor {
		char      name[32];
		char      caption[32];
		char      model[32];
		sf::Color color;
		int       armor;

		fired::ArmorClass type;
	};


	struct Armor {
		char      name[32];
		char      caption[32];
		char      model[32];
		sf::Color color;
		int       armor;

		fired::ArmorClass    type;
		fired::BaseBodypart *base;


		Armor(fired::BaseArmor *_armor, fired::World *world);
	};
}

#endif
