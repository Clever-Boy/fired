#include "game.hpp"

//======================================================================


fired::HintWindow::HintWindow() {
	win    = new fired::Window(sf::Vector2f(100, 50));

	text = new sf::Text();
	text->setFont(*game->getFont());
	text->setCharacterSize(12);
	text->setPosition(win->getOffset() + sf::Vector2f(30.0f, 360.0f));
	text->setColor(sf::Color::White);
}

//======================================================================


fired::HintWindow::~HintWindow() {
	delete win;
	delete text;
}

//======================================================================


void fired::HintWindow::update(fired::InventoryItem *item) {
	render(item);
}

//======================================================================


void fired::HintWindow::renderText(float x, float y, const char *caption, bool rightAligned) {
	if (rightAligned) {
		text->setString(sf::String(caption));
		text->setPosition(win->getOffset() + sf::Vector2f(x - text->getGlobalBounds().width, y));
		app->draw(*text);
	} else {
		text->setString(sf::String(caption));
		text->setPosition(win->getOffset() + sf::Vector2f(x, y));
		app->draw(*text);
	}
}

//======================================================================


void fired::HintWindow::render(fired::InventoryItem *item) {
	if (item == NULL) return;
	win->render();
}
