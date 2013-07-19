#include "game.hpp"

void fired::MainMenu::init(fired::Game *_game) {
	bgTexture.loadFromFile("data/img/gui/mainmenu/bg.jpg");
	bgSprite.setTexture(&bgTexture);
	bgTexture.setRepeated(true);
	bgSprite.setSize(sf::Vector2f(800,600));
	bgSprite.setTextureRect(sf::IntRect(0,0,800,600));

	menuItemTexture.loadFromFile("data/img/gui/mainmenu/menuitem.jpg");
	menuItemSprite.setTexture(menuItemTexture);
	menuItemTexture.setSmooth(true);

	logoTexture.loadFromFile("data/img/gui/mainmenu/logo.tga");
	logoSprite.setTexture(logoTexture);
	logoTexture.setSmooth(true);
	logoSprite.setScale(800.0/logoTexture.getSize().x, 800.0/logoTexture.getSize().x);

	menuFont.loadFromFile(MENU_FONT_FILE);

	game = _game;
	menuItem.init(game, &menuItemSprite, &menuFont, "Start game");
	return;
}


void fired::MainMenu::update(float frameClock) {
	render();
	menuItem.update(frameClock);
}


void fired::MainMenu::render() {
	game->app.draw(bgSprite);
	game->app.draw(logoSprite);
}
