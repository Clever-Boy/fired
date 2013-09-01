#include "game.hpp"

//======================================================================


fired::Armor::Armor(fired::BaseArmor *_armor, fired::World *world) {
	strncpy(name , _armor->name , sizeof(name));
	strncpy(model, _armor->model, sizeof(model));

	armor = _armor->armor;
	color = _armor->color;
	type  = _armor->type;


	switch (type) {
		case acHelm:
			base = world->getBodypart(model, bptHair);
			break;

		case acBody:
			base = world->getBodypart(model, bptBody);
			break;

		case acLegs:
			base = world->getBodypart(model, bptLegsF);
			break;

		case acShoe:
			base = world->getBodypart(model, bptShoeF);
			break;

		case acArms:
			base = world->getBodypart(model, bptArms);
			break;

		case acFist:
			base = world->getBodypart(model, bptFistF);
			break;
	}
}
