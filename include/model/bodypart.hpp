#ifndef __BODYPART
#define __BODYPART


namespace fired {
	enum BodypartType {
		bptLegsF,
		bptLegsB,
		bptFistF,
		bptFistB,
		bptShoeF,
		bptShoeB,
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
		sf::Sprite         *chunk;
		sf::Texture        *texture;
		sf::Vector2f        origin;
		sf::Vector2f        size;
		fired::BodypartType type;

		~BaseBodypart();
	};


	struct NewBaseBodypart {
		char                name[64];
		int                 sprite;
		sf::Vector2f        origin;
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
