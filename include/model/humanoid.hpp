/***********************************************************************
     * File       : humanoid.hpp
     * Created    : Aug 07, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __HUMANOID
#define __HUMANOID


#include "basemodel.hpp"


namespace fired {
	struct ModelHumanoid : Model {
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


		 ModelHumanoid(fired::Character *_owner, fired::BaseModelHumanoid *_base, float scale, fired::World *_world);
		~ModelHumanoid() {};

		void update();
		void updateParts();
		void respawn();
		void setWeapon(fired::BaseWeapon *weapon);

		void processAnimation();
		void processBodyAnimation();
		void processArmsAnimation();
	};
}

#endif
