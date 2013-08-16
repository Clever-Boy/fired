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
		bptWeapon,
		bptShot
	};


	struct BaseBodypart {
		char                name[32];
		sf::Sprite         *sprite;
		sf::Sprite         *chunk;
		sf::Texture        *texture;
		sf::Vector2f        offset;
		sf::Vector2f        origin;
		sf::Vector2f        size;
		sf::Color           color;
		fired::BodypartType type;

		~BaseBodypart();
	};


	struct Bodypart {
		fired::BaseBodypart *base;

		int                 *direction;
		sf::Vector2f         animOffset;
		float                animRotation;
	};
}

#endif
