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
		char      name[64];
		char      caption[64];
		char      model[64];
		sf::Color color;
		int       armor;

		fired::ArmorClass type;
	};


	struct Armor {
		char      name[64];
		char      caption[64];
		char      model[64];
		sf::Color color;
		int       armor;

		fired::ArmorClass    type;
		fired::BaseBodypart *base;


		Armor(fired::BaseArmor *_armor, fired::World *world);
	};
}

#endif
