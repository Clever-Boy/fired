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
		sf::Vector2f     weaponOffset;
	};


	struct BaseModelHumanoid : BaseModel {
		fired::BaseModelBodypart partLegsF;
		fired::BaseModelBodypart partLegsB;
		fired::BaseModelBodypart partShoeF;
		fired::BaseModelBodypart partShoeB;
		fired::BaseModelBodypart partFistF;
		fired::BaseModelBodypart partFistB;
		fired::BaseModelBodypart partHair;
		fired::BaseModelBodypart partBody;
		fired::BaseModelBodypart partArms;
		fired::BaseModelBodypart partHead;
	};



	struct NewBaseModel {
		fired::ModelType type;
		sf::Vector2f     size;
		sf::Vector2f     weaponOffset;
	};


	struct NewBaseModelHumanoid : NewBaseModel {
		fired::BaseModelBodypart partLegsF;
		fired::BaseModelBodypart partLegsB;
		fired::BaseModelBodypart partShoeF;
		fired::BaseModelBodypart partShoeB;
		fired::BaseModelBodypart partFistF;
		fired::BaseModelBodypart partFistB;
		fired::BaseModelBodypart partHair;
		fired::BaseModelBodypart partBody;
		fired::BaseModelBodypart partArms;
		fired::BaseModelBodypart partHead;
	};



	struct Model {
		fired::Character *owner;
		fired::World     *world;

		float modelScale;
		std::vector<fired::Bodypart*> bodyParts;


		virtual ~Model();

		virtual void update()      {};
		virtual void updateParts() {};
		virtual void respawn()     {};
		virtual void setWeapon(fired::BaseWeapon*) {};

		void render();
		void explode(sf::Vector2f shot, float knockback);

		void initPart(fired::Bodypart *part, fired::BaseBodypart *base, sf::Color color, sf::Vector2f offset, int *direction);
		void drawPart(fired::Bodypart *part);
		void resetPart(fired::Bodypart *part);
		void chunkPart(fired::Bodypart *part, sf::Vector2f shot, float knockback);

		void resetAnimation();
	};
}

#endif
