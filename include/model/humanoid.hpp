#ifndef __HUMANOID
#define __HUMANOID


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "basemodel.hpp"


namespace fired {
	class ModelHumanoid : public Model {
	private:
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


		fired::CharAnimationType bodyAnimation;
		fired::CharAnimationType armsAnimation;

		float bodyAnimationTime;
		float armsAnimationTime;

		int bodyFrame;
		int armsFrame;


	public:
		void init(fired::Game *_game, fired::Character *_owner, fired::BaseModelHumanoid *base);
		void update();

		void processAnimation();
		void processBodyAnimation();
		void processArmsAnimation();
	};
}

#endif
