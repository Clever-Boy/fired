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
		caShooting
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
		fired::BaseBodypart *partWeapon;
	};



	class Model {
	protected:
		fired::Game      *game;
		fired::Settings  *settings;
		fired::Character *owner;
		sf::RenderWindow *app;

		float modelScale;
		std::vector<fired::Bodypart*> bodyParts;


	public:
		void deinit();
		void render();
		virtual void update() {};

		void initPart(fired::Bodypart *part, fired::BaseBodypart *base, int *direction);
		void drawPart(fired::Bodypart *part);
		void resetPart(fired::Bodypart *part);

		void resetAnimation();
	};
}

#endif
