#include "game.hpp"

//======================================================================


fired::InventoryWindow::InventoryWindow(fired::Character *_owner) {
	owner = _owner;
	win = new fired::Window(sf::Vector2f(450, 500));
}

//======================================================================


fired::InventoryWindow::~InventoryWindow() {
	delete win;
}

//======================================================================


void fired::InventoryWindow::render() {
	win->render();
}
