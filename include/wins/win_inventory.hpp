#ifndef __WIN_INVENTORY
#define __WIN_INVENTORY


#include "win_base.hpp"


namespace fired {
	class InventoryWindow {
	private:
		fired::Window    *win;
		fired::Character *owner;


	public:
		 InventoryWindow(fired::Character *_owner);
		~InventoryWindow();

		void render();
	};
}

#endif
