/***********************************************************************
     * File       : model_animal.hpp
     * Created    : Jul 30, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MODEL_ANIMAL
#define __MODEL_ANIMAL


#include "model_base.hpp"


namespace fired {
	struct BaseModelAnimal : BaseModel {
		fired::BaseModelBodypart partLegsFF;
		fired::BaseModelBodypart partLegsBF;
		fired::BaseModelBodypart partLegsFB;
		fired::BaseModelBodypart partLegsBB;
		fired::BaseModelBodypart partBody;
		fired::BaseModelBodypart partTail;
		fired::BaseModelBodypart partHead;
	};


	struct ModelAnimalColors : ModelColors {
		sf::Color partLegsFF;
		sf::Color partLegsBF;
		sf::Color partLegsFB;
		sf::Color partLegsBB;
		sf::Color partBody;
		sf::Color partTail;
		sf::Color partHead;
	};


	struct ModelAnimalBones {
		fired::ModelBone legsFF;
		fired::ModelBone legsBF;
		fired::ModelBone legsFB;
		fired::ModelBone legsBB;
		fired::ModelBone tail;
	};


	struct ModelAnimal : Model {
		fired::BaseModelAnimal  *base;
		fired::ModelAnimalBones  bones;

		fired::Bodypart partLegsFF;
		fired::Bodypart partLegsBF;
		fired::Bodypart partLegsFB;
		fired::Bodypart partLegsBB;
		fired::Bodypart partBody;
		fired::Bodypart partTail;
		fired::Bodypart partHead;


		fired::CharAnimationType bodyAnimation;

		float bodyAnimationTime;
		int   bodyFrame;
		float legsDiff;


		 ModelAnimal(fired::Character *_owner, fired::BaseModelAnimal *_base, fired::ModelAnimalColors *modelColors, float scale, fired::World *_world);
		~ModelAnimal() {};

		void updateAnimation();
		void updateParts(fired::ModelAnimalColors *modelColors);
		void updateBones();
		void respawn();

		void processAnimation();
		void processBones();
	};
}

#endif
