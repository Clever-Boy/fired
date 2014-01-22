/***********************************************************************
     * File       : bodypart.hpp
     * Created    : Aug 07, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __BODYPART
#define __BODYPART


namespace fired {
	enum BodypartType {
		bptLegs,
		bptFist,
		bptShoe,
		bptBody,
		bptHair,
		bptHead,
		bptArms,
		bptWeapon
	};


	struct BaseBodypart {
		char                name[64];
		sf::Sprite         *sprite;
		sf::Vector2f        origin;
		sf::Vector2f        size;
		fired::BodypartType type;
	};


	struct BaseModelBodypart {
		fired::BaseBodypart *part;
		sf::Color            color;
		sf::Vector2f         offset;
	};


	struct Bodypart {
		fired::BaseBodypart *base;
		sf::Vector2f         offset;
		sf::Color            color;

		int                 *direction;
		sf::Vector2f         animOffset;
		float                animRotation;
	};
}

#endif
