#ifndef __PHYS
#define __PHYS


namespace fired {
	struct Phys {
		sf::Vector2f  size;
		sf::Vector2f  pos;
		sf::Vector2f  velocity;
		sf::Vector2f  acceleration;

		sf::FloatRect rect;
		sf::Vector2f  center;

		bool isMoving;
		bool onGround;

		bool jumpdown;
		int  jumpdownLevel;

		Phys();
		void calculate();
	};
}

#endif
