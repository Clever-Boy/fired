#ifndef __MOUSE
#define __MOUSE


namespace fired {
	struct Mouse {
		sf::Vector2f pos;
		sf::Texture *mouseTex;
		sf::Sprite  *mouseCur;


		 Mouse();
		~Mouse();

		void update();
		void render();
	};
}

#endif
