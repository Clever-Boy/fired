#include "game.hpp"

//======================================================================


fired::CharacterWindow::CharacterWindow(fired::Character *_owner) {
	owner  = _owner;
	win    = new fired::Window(sf::Vector2f(300, 100));

	text = new sf::Text();
	text->setFont(*game->getFont());
	text->setCharacterSize(16);
	text->setPosition(win->getOffset() + sf::Vector2f(30.0f, 360.0f));
	text->setColor(sf::Color::White);
}

//======================================================================


fired::CharacterWindow::~CharacterWindow() {
	delete win;
	delete text;
}

//======================================================================


void fired::CharacterWindow::update() {
	render();
}

//======================================================================


void fired::CharacterWindow::renderText(float x, float y, const char *caption) {
	text->setString(sf::String(caption));
	text->setPosition(win->getOffset() + sf::Vector2f(x, y));
	app->draw(*text);
}

//======================================================================


void fired::CharacterWindow::render() {
	win->render();
}
