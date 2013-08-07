#ifndef __MODEL
#define __MODEL


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
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		fired::Character *owner;
		sf::RenderWindow *app;

		fired::CharAnimationType bodyAnimation;
		fired::CharAnimationType armsAnimation;

		float bodyAnimationTime;
		float armsAnimationTime;

		int bodyFrame;
		int armsFrame;

		fired::Bodypart partLegsF;
		fired::Bodypart partLegsB;
		fired::Bodypart partShoeF;
		fired::Bodypart partShoeB;
		fired::Bodypart partFistF;
		fired::Bodypart partFistB;
		fired::Bodypart partHair;
		fired::Bodypart partBody;
		fired::Bodypart partArms;
		fired::Bodypart partHead;
		fired::Bodypart partWeapon;

		std::vector<fired::Bodypart*> bodyParts;


	public:
		void init(fired::Game *_game, fired::Character *_owner, fired::BaseModel *base);
		void deinit();
		void update();
		void render();

		void initPart(fired::Bodypart *part, sf::Vector2f offset, const char *imgFile, int *direction);
		void drawPart(fired::Bodypart *part);
		void deinitPart(fired::Bodypart *part);
		void resetPart(fired::Bodypart *part);

		void processAnimation();
		void resetAnimation();
		void processBodyAnimation();
		void processArmsAnimation();
	};
}

#endif
