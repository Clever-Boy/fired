#ifndef __MODEL
#define __MODEL


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "bodypart.hpp"


namespace fired {
	class Model {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		fired::Character *owner;
		sf::RenderWindow *app;

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

		std::vector<fired::Bodypart*> bodyParts;

	public:
		void init(fired::Game *_game, fired::Character *_owner);
		void deinit();
		void update();
		void render();

		void initPart(fired::Bodypart *part, sf::Vector2f offset, const char *imgFile);
		void drawPart(fired::Bodypart *part);
		void deinitPart(fired::Bodypart *part);
	};
}

#endif
