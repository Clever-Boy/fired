#ifndef __MENUITEM
#define __MENUITEM

#include <SFML/Graphics.hpp>

namespace fired {
	class MenuItem {
	private:
		sf::String Caption;

	public:
		void Init();
		void Update();
		void Render();
	};
}
#endif
