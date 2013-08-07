#ifndef __BODYPART
#define __BODYPART


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	enum BodypartType {
		bptLegsF,
		bptLegsB,
		bptFistF,
		bptFistB,
		bptShoeF,
		bptShoeB,
		bptBody,
		bptHair,
		bptHead,
		bptArms,
		bptWeapon
	};


	struct Bodypart {
		char                name[32];
		sf::Sprite         *sprite;
		sf::Texture        *texture;
		sf::Vector2f        offset;
		sf::Color           color;
		int                *direction;
		fired::BodypartType type;

		sf::Vector2f  animOffset;
		float         animRotation;
	};
}

#endif
