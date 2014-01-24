/***********************************************************************
     * File       : armor.hpp
     * Created    : Sep 01, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __ARMOR
#define __ARMOR


namespace fired {
	enum ArmorClass {
		acNull,
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
		sf::Color color;
		int       armor;

		fired::ArmorClass type;
		fired::BaseBodypart *base;
	};
}

#endif
