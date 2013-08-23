#ifndef __PHYS
#define __PHYS


namespace fired {
	struct Phys {
		sf::Vector2f  size;
		sf::Vector2f  pos;
		sf::Vector2f  velocity;
		sf::Vector2f  acceleration;

		sf::Vector2f  headSize;
		sf::Vector2f  headOffset;

		sf::FloatRect rect;
		sf::FloatRect head;
		sf::Vector2f  center;
		bool isMoving;
		bool onGround;


		void calculate();
	};
}

#endif
