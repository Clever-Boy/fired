#ifndef __WIN
#define __WIN


namespace fired {
	class Window {
	private:
		sf::Texture *windowTexBG;
		sf::Texture *windowTexL;
		sf::Texture *windowTexR;
		sf::Texture *windowTexT;
		sf::Texture *windowTexB;
		sf::Texture *windowTexLT;
		sf::Texture *windowTexRT;
		sf::Texture *windowTexLB;
		sf::Texture *windowTexRB;

		sf::RectangleShape *windowSprBG;
		sf::RectangleShape *windowSprL;
		sf::RectangleShape *windowSprR;
		sf::RectangleShape *windowSprT;
		sf::RectangleShape *windowSprB;
		sf::RectangleShape *windowSprLT;
		sf::RectangleShape *windowSprRT;
		sf::RectangleShape *windowSprLB;
		sf::RectangleShape *windowSprRB;

		sf::Vector2f size;
		sf::Vector2f offset;


	public:
		 Window(sf::Vector2f _size);
		~Window();

		void render();
		void initPart(sf::Texture **tex, sf::RectangleShape **spr, sf::Vector2i _size, sf::Vector2f _pos, const char *texFile);
	};
}

#endif
