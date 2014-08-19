/***********************************************************************
     * File       : model_base.hpp
     * Created    : Aug 07, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MODEL_BASE
#define __MODEL_BASE


#include "model_bodypart.hpp"
#include "item.hpp"


namespace fired {
	enum CharAnimationType {
		caNone,
		caMoving,
		caJumping,
		caShooting,
		caMeleeAttack,
		caBroadAttack
	};


	enum ModelType {
		mtHumanoid,
		mtAnimal,
		mtSpider
	};


	struct BaseModel {
		char             name[64];
		fired::ModelType type;
		sf::Vector2f     size;
		sf::Vector2f     weaponOffset;
	};


	struct ModelColors {};


	struct Model {
		fired::Character *owner;
		fired::World     *world;

		float modelScale;
		std::vector<fired::Bodypart*>  bodyParts;
		std::vector<fired::ModelBone*> bodyBones;


		virtual ~Model();

		virtual void updateAnimation()             {};
		virtual void updateParts()                 {};
		virtual void updateBones()                 {};
		virtual void respawn()                     {};
		virtual void processAnimation()            {};
		virtual void processBones()                {};
		virtual void setWeapon(fired::BaseWeapon*) {};

		virtual sf::Vector2f getBarrelPos();

		void update();
		void render();
		void explode(sf::Vector2f shot, float knockback);

		void initPart(fired::Bodypart *part, fired::BaseModelBodypart *base, sf::Color color, fired::BaseArmor *armor, int *direction);
		void drawPart(fired::Bodypart *part);
		void resetPart(fired::Bodypart *part);
		void chunkPart(fired::Bodypart *part, sf::Vector2f shot, float knockback);
		void initBone(fired::ModelBone *bone, sf::Vector2f start, sf::Vector2f end);

		void resetAnimation();
	};
}

#endif
