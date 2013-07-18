#ifndef __MAINMENU
#define __MAINMENU

#include <SFML/Graphics.hpp>
#include "menuitem.hpp"

namespace fired {
	class MainMenu {
	private:
		fired::MenuItem MenuItem;

	public:
		void Init();
		void Update();
	};
}
#endif
