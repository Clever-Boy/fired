#ifndef __HUMANOID
#define __HUMANOID


#include "basemodel.hpp"


namespace fired {
	class ModelHumanoid : public Model {
	private:
		fired::BaseModelHumanoid *base;

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
		 ModelHumanoid(fired::Character *_owner, fired::BaseModelHumanoid *_base, float scale, fired::World *_world);
		~ModelHumanoid() {};

		void update();
		void updateParts();
		void respawn();
		void headshot();
		void setWeapon(fired::BaseWeapon *weapon);

		void processAnimation();
		void processBodyAnimation();
		void processArmsAnimation();
	};
}

#endif
