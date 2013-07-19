#include "game.hpp"

void fired::MainMenu::init(fired::Game *_game) {
	game    = _game;
	xOffset = 0;

	bgTexture.loadFromFile("data/img/gui/mainmenu/bg.jpg");
	bgSprite.setTexture(&bgTexture);
	bgTexture.setRepeated(true);
	bgSprite.setSize(sf::Vector2f(800,600));

	menuItemTexture.loadFromFile("data/img/gui/mainmenu/menuitem.jpg");
	menuItemSprite.setTexture(menuItemTexture);
	menuItemTexture.setSmooth(true);

	logoTexture.loadFromFile("data/img/gui/mainmenu/logo.tga");
	logoSprite.setTexture(logoTexture);
	logoTexture.setSmooth(true);
	logoSprite.setScale(800.0/logoTexture.getSize().x, 800.0/logoTexture.getSize().x);

	menuFont.loadFromFile(MENU_FONT_FILE);
	menuItem.init(game, &menuItemSprite, &menuFont, "Start game");
	return;
}


void fired::MainMenu::update(float frameClock) {
	xOffset += frameClock * MENU_BG_SPEED;
	if (xOffset > bgTexture.getSize().x) xOffset -= bgTexture.getSize().x;

	render();
	menuItem.update(frameClock);
}


void fired::MainMenu::render() {
	bgSprite.setTextureRect(sf::IntRect(xOffset, 0, 800.0, 600));
	game->app.draw(bgSprite);
	game->app.draw(logoSprite);
}
