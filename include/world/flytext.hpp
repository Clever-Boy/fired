#ifndef __FLYTEXT
#define __FLYTEXT


namespace fired {
	struct FlyText {
		sf::Vector2f pos;
		sf::Color    color;
		float        life;

		sf::String  *flyStr;
		sf::Text    *flyTxt;


		 FlyText(sf::Vector2f _pos, sf::Color _color, int size, const char *text);
		~FlyText();

		bool update();
		void render();
	};
}

#endif
