#ifndef __BASEMODEL
#define __BASEMODEL


#include "bodypart.hpp"
#include "items.hpp"


namespace fired {
	enum CharAnimationType {
		caNone,
		caMoving,
		caJumping,
		caShooting,
		caReloading,
		caMeleeAttack,
		caBroadAttack
	};


	enum ModelType {
		mtHumanoid
	};



	struct BaseModel {
		char             name[64];
		fired::ModelType type;
		sf::Vector2f     size;
	};


	struct BaseModelHumanoid : BaseModel {
		fired::BaseBodypart *partLegsF;
		fired::BaseBodypart *partLegsB;
		fired::BaseBodypart *partShoeF;
		fired::BaseBodypart *partShoeB;
		fired::BaseBodypart *partFistF;
		fired::BaseBodypart *partFistB;
		fired::BaseBodypart *partHair;
		fired::BaseBodypart *partBody;
		fired::BaseBodypart *partArms;
		fired::BaseBodypart *partHead;

		sf::Color partLegsFColor;
		sf::Color partLegsBColor;
		sf::Color partShoeFColor;
		sf::Color partShoeBColor;
		sf::Color partFistFColor;
		sf::Color partFistBColor;
		sf::Color partHairColor;
		sf::Color partBodyColor;
		sf::Color partArmsColor;
		sf::Color partHeadColor;
	};



	struct Model {
		fired::Character *owner;
		fired::World     *world;

		float modelScale;
		std::vector<fired::Bodypart*> bodyParts;


		virtual ~Model();

		virtual void headshot()    {};
		virtual void update()      {};
		virtual void updateParts() {};
		virtual void respawn()     {};
		virtual void setWeapon(fired::BaseWeapon*) {};

		void render();
		void explode(sf::Vector2f shot, float knockback);

		void initPart(fired::Bodypart *part, fired::BaseBodypart *base, sf::Color color, int *direction);
		void drawPart(fired::Bodypart *part);
		void resetPart(fired::Bodypart *part);
		void chunkPart(fired::Bodypart *part, sf::Vector2f shot, float knockback);

		void resetAnimation();
	};
}

#endif
