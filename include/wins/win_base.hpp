#ifndef __WIN_BASE
#define __WIN_BASE


namespace fired {
	class Window {
	private:
		sf::RectangleShape *window;

		sf::Vector2f size;
		sf::Vector2f offset;


	public:
		 Window(sf::Vector2f _size);
		~Window();

		void render();

		sf::Vector2f getOffset() {return offset; };
		sf::Vector2f getSize()   {return size;   };
	};
}

#endif
