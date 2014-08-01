/***********************************************************************
     * File       : model_spider.hpp
     * Created    : Jul 31, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MODEL_SPIDER
#define __MODEL_SPIDER


#include "model_base.hpp"


namespace fired {
	struct BaseModelSpider : BaseModel {
		fired::BaseModelBodypart partLegsF1;
		fired::BaseModelBodypart partLegsF2;
		fired::BaseModelBodypart partLegsF3;
		fired::BaseModelBodypart partLegsF4;
		fired::BaseModelBodypart partShoeF1;
		fired::BaseModelBodypart partShoeF2;
		fired::BaseModelBodypart partShoeF3;
		fired::BaseModelBodypart partShoeF4;
		fired::BaseModelBodypart partBody;
		fired::BaseModelBodypart partHead;
	};


	struct ModelSpiderColors : ModelColors {
		sf::Color partLegsF1;
		sf::Color partLegsF2;
		sf::Color partLegsF3;
		sf::Color partLegsF4;
		sf::Color partShoeF1;
		sf::Color partShoeF2;
		sf::Color partShoeF3;
		sf::Color partShoeF4;
		sf::Color partBody;
		sf::Color partHead;
	};


	struct ModelSpiderBones {
		fired::ModelBone legsF1;
		fired::ModelBone legsF2;
		fired::ModelBone legsF3;
		fired::ModelBone legsF4;
		fired::ModelBone shoeF1;
		fired::ModelBone shoeF2;
		fired::ModelBone shoeF3;
		fired::ModelBone shoeF4;
	};


	struct ModelSpider : Model {
		fired::BaseModelSpider  *base;
		fired::ModelSpiderBones  bones;

		fired::Bodypart partLegsF1;
		fired::Bodypart partLegsF2;
		fired::Bodypart partLegsF3;
		fired::Bodypart partLegsF4;
		fired::Bodypart partShoeF1;
		fired::Bodypart partShoeF2;
		fired::Bodypart partShoeF3;
		fired::Bodypart partShoeF4;
		fired::Bodypart partBody;
		fired::Bodypart partHead;


		fired::CharAnimationType bodyAnimation;

		float bodyAnimationTime;
		int   bodyFrame;


		 ModelSpider(fired::Character *_owner, fired::BaseModelSpider *_base, fired::ModelSpiderColors *modelColors, float scale, fired::World *_world);
		~ModelSpider() {};

		void updateAnimation();
		void updateParts(fired::ModelSpiderColors *modelColors);
		void updateBones();
		void respawn();

		void processAnimation();
		void processBones();
	};
}

#endif
