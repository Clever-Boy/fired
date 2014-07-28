/***********************************************************************
     * File       : model_humanoid.hpp
     * Created    : Aug 07, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MODEL_HUMANOID
#define __MODEL_HUMANOID


#include "model_base.hpp"


namespace fired {
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


	struct ModelHumanoidColors : ModelColors {
		sf::Color partLegsF;
		sf::Color partLegsB;
		sf::Color partShoeF;
		sf::Color partShoeB;
		sf::Color partFistF;
		sf::Color partFistB;
		sf::Color partHair;
		sf::Color partBody;
		sf::Color partArms;
		sf::Color partHead;
	};


	struct ModelHumanoidBones {
		fired::ModelBone legsF;
		fired::ModelBone legsB;
		fired::ModelBone armsF;
		fired::ModelBone armsB;
		fired::ModelBone weapon;
	};


	struct ModelHumanoid : Model {
		fired::BaseModelHumanoid  *base;
		fired::ModelHumanoidBones  bones;

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


		 ModelHumanoid(fired::Character *_owner, fired::BaseModelHumanoid *_base, fired::ModelHumanoidColors *modelColors, float scale, fired::World *_world);
		~ModelHumanoid() {};

		void update();
		void updateParts(fired::ModelHumanoidColors *modelColors);
		void respawn();
		void setWeapon(fired::BaseWeapon *weapon);

		void processAnimation();
		void processBodyAnimation();
		void processArmsAnimation();
	};
}

#endif
