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

	menuFont.loadFromFile("data/fonts/advanced_pixel-7.ttf");
	menuCaption.setFont(menuFont);
	menuCaption.setCharacterSize(48);

	fillMenu();
	return;
}


void fired::MainMenu::update(float frameClock) {
	xOffset += frameClock * MENU_BG_SPEED;
	if (xOffset > bgTexture.getSize().x) xOffset -= bgTexture.getSize().x;

	//This gonna move to change current menu function
	menuCaption.setString(currentMenu->caption);
	menuCaption.setPosition(sf::Vector2f(50 + (menuItemTexture.getSize().x - menuCaption.getGlobalBounds().width) / 2, 150));

	render();
	for (int i = 0; i < currentMenu->subMenu.size(); i++) currentMenu->subMenu[i]->update(frameClock);
}


void fired::MainMenu::render() {
	bgSprite.setTextureRect(sf::IntRect(xOffset, 0, game->settings.window.width, game->settings.window.height));
	game->app.draw(bgSprite);
	game->app.draw(logoSprite);
	game->app.draw(menuCaption);
}


void fired::MainMenu::menuItemAdd(const char *_caption, fired::MenuItem *_parent) {
	menuItems.push_back(new fired::MenuItem);
	menuItems.back()->init(game, &menuItemSprite, &menuFont, _caption, _parent);
}


void fired::MainMenu::fillMenu() {
	fired::MenuItem *curParent;

	menuItemAdd("Main menu", NULL);
	currentMenu = menuItems[0];

	curParent   = menuItems[0];
	menuItemAdd("Start game", curParent);
	menuItemAdd("Load game", curParent);
	menuItemAdd("Exit", curParent);

	for (int i = 0; i < menuItems.size(); i++) menuItems[i]->addToParent();
}


void fired::MainMenu::click(sf::Vector2i pos) {
	int index = (pos.y - MENU_Y_OFFSET) / MENU_Y_DIFF;
	if ((index < menuItems.size()) && ((pos.y - MENU_Y_OFFSET) % MENU_Y_DIFF < MENU_HEIGHT)) menuItems[index]->click();
}
