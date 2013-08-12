#ifndef __BASEMODEL
#define __BASEMODEL


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "bodypart.hpp"


namespace fired {
	enum CharAnimationType {
		caNone,
		caMoving,
		caJumping,
		caShooting,
		caReloading
	};


	enum ModelType {
		mtHumanoid
	};



	struct BaseModel {
		char             name[32];
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
	};



	class Model {
	protected:
		fired::Character *owner;
		fired::World     *world;

		float modelScale;
		std::vector<fired::Bodypart*> bodyParts;


	public:
		virtual ~Model();

		virtual void headshot() {};
		virtual void update()   {};
		virtual void respawn()  {};
		virtual void setWeapon(fired::BaseWeapon*) {};

		void render();
		void explode(sf::Vector2f shot, float knockback);

		void initPart(fired::Bodypart *part, fired::BaseBodypart *base, int *direction);
		void drawPart(fired::Bodypart *part);
		void resetPart(fired::Bodypart *part);
		void chunkPart(fired::Bodypart *part, sf::Vector2f shot, float knockback);

		void resetAnimation();
	};
}

#endif
