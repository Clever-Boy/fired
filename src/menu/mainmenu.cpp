#include "game.hpp"

void fired::MainMenu::init(fired::Game *_game) {
	game    = _game;
	xOffset = 0;

	bgTexture.loadFromFile("data/img/gui/mainmenu/bg.jpg");
	bgSprite.setTexture(&bgTexture);
	bgTexture.setRepeated(true);
	bgSprite.setSize(sf::Vector2f(game->settings.window.width, game->settings.window.height));

	menuItemTexture.loadFromFile("data/img/gui/mainmenu/menuitem.jpg");
	menuItemSprite.setTexture(menuItemTexture);
	menuItemTexture.setSmooth(true);

	logoTexture.loadFromFile("data/img/gui/mainmenu/logo.tga");
	logoSprite.setTexture(logoTexture);
	logoTexture.setSmooth(true);

	if (logoTexture.getSize().x > game->settings.window.width)
		logoSprite.setScale((float)game->settings.window.width/logoTexture.getSize().x, (float)game->settings.window.width/logoTexture.getSize().x);
	else
		logoSprite.setPosition((game->settings.window.width - logoTexture.getSize().x) / 2, 0);

	menuFont.loadFromFile(MENU_FONT_FILE);
	fillMenu();
	return;
}


void fired::MainMenu::update(float frameClock) {
	xOffset += frameClock * MENU_BG_SPEED;
	if (xOffset > bgTexture.getSize().x) xOffset -= bgTexture.getSize().x;

	render();
	for (int i = 0; i < menuItems.size(); i++) menuItems[i].update(frameClock);
}


void fired::MainMenu::render() {
	bgSprite.setTextureRect(sf::IntRect(xOffset, 0, game->settings.window.width, game->settings.window.height));
	game->app.draw(bgSprite);
	game->app.draw(logoSprite);
}


void fired::MainMenu::menuItemAdd(const char *_caption) {
	fired::MenuItem menuItem;

	menuItem.init(game, &menuItemSprite, &menuFont, _caption);
	menuItems.push_back(menuItem);
}


void fired::MainMenu::fillMenu() {
	menuItemAdd("Start game");
	menuItemAdd("Load game");
	menuItemAdd("Exit");

	// This will be the structMenu function later
	for (int i = 0; i < menuItems.size(); i++) menuItems[i].setIndex(i);
}
