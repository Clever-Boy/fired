#ifndef __MOUSE
#define __MOUSE


namespace fired {
	class Mouse {
	private:
		sf::Vector2f pos;
		sf::Texture *mouseTex;
		sf::Sprite  *mouseCur;


	public:
		 Mouse();
		~Mouse();

		void update();
		void render();

		sf::Vector2f getPos() {return pos; };
	};
}

#endif
