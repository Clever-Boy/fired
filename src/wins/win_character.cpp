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


void fired::CharacterWindow::renderText(float x, float y, const char *caption, bool rightAligned) {
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


void fired::CharacterWindow::render() {
	char str[128];
	win->render();

	snprintf(str, sizeof(str), "%d", owner->level);
	renderText( 10, 10, "Level", false);
	renderText(290, 10, str    , true);

	snprintf(str, sizeof(str), "%d / %d", owner->baseStats.HP, owner->baseStats.maxHP);
	renderText( 10, 30, "HP", false);
	renderText(290, 30, str , true);

	snprintf(str, sizeof(str), "%ld", owner->XP);
	renderText( 10, 50, "XP", false);
	renderText(290, 50, str , true);

	snprintf(str, sizeof(str), "%ld", owner->needXP);
	renderText( 10, 70, "Next level", false);
	renderText(290, 70, str         , true);
}
