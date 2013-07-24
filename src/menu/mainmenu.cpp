#include "game.hpp"


void fired::MainMenu::init(fired::Game *_game) {
	game    = _game;
	xOffset = 0;

	game->musicTheme.openFromFile("data/snd/themes/mainmenu.ogg");
	game->musicTheme.play();

	clickBuffer = new sf::SoundBuffer();
	clickSound  = new sf::Sound();
	clickBuffer->loadFromFile("data/snd/misc/click.wav");
	clickSound->setBuffer(*clickBuffer);

	bgTexture       = new sf::Texture();
	menuItemTexture = new sf::Texture();
	logoTexture     = new sf::Texture();

	bgSprite       = new sf::RectangleShape();
	menuItemSprite = new sf::Sprite();
	logoSprite     = new sf::Sprite();
	menuCaption    = new sf::Text();

	bgTexture->loadFromFile("data/img/gui/mainmenu/bg.jpg");
	bgSprite->setTexture(bgTexture);
	bgTexture->setRepeated(true);
	bgSprite->setSize(sf::Vector2f(game->settings.window.width, game->settings.window.height));

	menuItemTexture->loadFromFile("data/img/gui/mainmenu/menuitem.jpg");
	menuItemSprite->setTexture(*menuItemTexture);
	menuItemTexture->setSmooth(true);

	logoTexture->loadFromFile("data/img/gui/mainmenu/logo.tga");
	logoSprite->setTexture(*logoTexture);
	logoTexture->setSmooth(true);

	if (logoTexture->getSize().x > game->settings.window.width)
		logoSprite->setScale((float)game->settings.window.width/logoTexture->getSize().x, (float)game->settings.window.width/logoTexture->getSize().x);
	else
		logoSprite->setPosition((game->settings.window.width - logoTexture->getSize().x) / 2, 0);

	menuCaption->setFont(game->font);
	menuCaption->setCharacterSize(48);

	fillMenu();
	updateSettings();
}



void fired::MainMenu::deinit() {
	for (int i = 0; i < menuItems.size(); menuItems[i]->deinit(), free(menuItems[i]), i++);
	menuItems.clear();

	game->musicTheme.stop();
	clickSound->stop();

	delete clickSound;
	delete clickBuffer;

	delete bgTexture;
	delete menuItemTexture;
	delete logoTexture;

	delete logoSprite;
	delete menuItemSprite;
	delete bgSprite;
	delete menuCaption;
}



void fired::MainMenu::update(float frameClock) {
	xOffset += frameClock * MENU_BG_SPEED;
	if (xOffset > bgTexture->getSize().x) xOffset -= bgTexture->getSize().x;

	processAnimation(frameClock);
	render();
	for (int i = 0; i < currentMenu->subMenu.size(); i++) currentMenu->subMenu[i]->update(frameClock);

	game->mouse.update(frameClock);
}



void fired::MainMenu::render() {
	bgSprite->setTextureRect(sf::IntRect(xOffset, 0, game->settings.window.width, game->settings.window.height));
	game->app.draw(*bgSprite);
	game->app.draw(*logoSprite);
	game->app.draw(*menuCaption);
}



void fired::MainMenu::processEvent(sf::Event event) {
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) click(sf::Mouse::getPosition(game->app));
}



void fired::MainMenu::click(sf::Vector2i pos) {
	if (animation != atNone) return;

	for (int i = 0; i < currentMenu->subMenu.size(); i++) 
		if (currentMenu->subMenu[i]->sprite->getLocalBounds().contains(sf::Vector2f(pos) - currentMenu->subMenu[i]->pos)) {
			clickSound->play();
			currentMenu->subMenu[i]->click();
		}
}



void fired::MainMenu::updateSettings() {
	clickSound->setVolume(game->settings.volume.sound);
}



void fired::MainMenu::setNextMenu(fired::MenuItem *menuItem) {
	nextMenu = menuItem;
	initAnimation(atDown);
}



void fired::MainMenu::switchMenu(fired::MenuItem *menuItem) {
	currentMenu = menuItem;
	menuCaption->setString(*currentMenu->caption);
	menuCaption->setPosition(sf::Vector2f(MENU_X_OFFSET + (menuItemTexture->getSize().x - menuCaption->getGlobalBounds().width) / 2, MENU_Y_OFFSET));
	initAnimation(atUp);
}



void fired::MainMenu::initAnimation(fired::MenuAnimationType animType) {
	animation = animType;

	switch (animation) {
		case atNone:
			for (int i = 0; i < currentMenu->subMenu.size(); i++) {
				currentMenu->subMenu[i]->timeOffset = 0;
				currentMenu->subMenu[i]->yOffset = 0;
			}
			break;

		case atUp:
			for (int i = 0; i < currentMenu->subMenu.size(); i++) {
				currentMenu->subMenu[i]->timeOffset = -0.05 * i;
				currentMenu->subMenu[i]->yOffset = game->settings.window.height;
			}
			break;

		case atDown:
			for (int i = 0; i < currentMenu->subMenu.size(); i++) {
				currentMenu->subMenu[i]->timeOffset = -0.05 * (currentMenu->subMenu.size() - i - 1);
				currentMenu->subMenu[i]->yOffset = 0;
			}
			break;
	}
}



void fired::MainMenu::processAnimation(float frameClock) {
	switch (animation) {
		case atNone:
			break;

		case atUp:
			for (int i = 0; i < currentMenu->subMenu.size(); i++) {
				currentMenu->subMenu[i]->timeOffset += frameClock;
				if (currentMenu->subMenu[i]->timeOffset > 0)
					currentMenu->subMenu[i]->yOffset = 250.0 * exp(-currentMenu->subMenu[i]->timeOffset * 16.0 + 2.0) - 25.0;

				if (currentMenu->subMenu[i]->yOffset < 0)
					currentMenu->subMenu[i]->yOffset = 0;
			}

			if (currentMenu->subMenu[currentMenu->subMenu.size() - 1]->yOffset == 0) initAnimation(atNone);
			break;

		case atDown:
			for (int i = 0; i < currentMenu->subMenu.size(); i++) {
				currentMenu->subMenu[i]->timeOffset += frameClock;
				if (currentMenu->subMenu[i]->timeOffset > 0)
					currentMenu->subMenu[i]->yOffset = 15.0 * (exp(currentMenu->subMenu[i]->timeOffset * 12.0 + 2.0) - exp(2));
			}

			if (currentMenu->subMenu[0]->yOffset > game->settings.window.height) {
				switchMenu(nextMenu);
				initAnimation(atUp);
			}
			break;
	}
}



void fired::MainMenu::menuItemAdd(const char *_caption, fired::MenuItem *_parent, fired::MenuItemType itemType = itSubmenu, fired::Handler handlerFunc = NULL) {
	menuItems.push_back(new fired::MenuItem);
	menuItems.back()->init(game, menuItemSprite, &game->font, _caption, _parent, itemType, handlerFunc);
}



void fired::MainMenu::fillMenuBack() {
	int menuItemCount = menuItems.size();
	for (int i = 1; i < menuItemCount; i++)
		if (menuItems[i]->itemType != itBack)
			menuItemAdd("Back", menuItems[i], itBack);
}



void fired::MainMenu::fillMenu() {
	fired::MenuItem *curParent;

	menuItemAdd("Main menu", NULL);

	curParent = menuItems[0];
	menuItemAdd("Start game", curParent);
	menuItemAdd("Load game" , curParent);
	menuItemAdd("Options"   , curParent);
	menuItemAdd("Credits"   , curParent, itButton, &fired::Handlers::buttonCredits);
	menuItemAdd("Exit"      , curParent, itButton, &fired::Handlers::buttonExit);

	curParent = menuItems[3];
	menuItemAdd("Video"   , curParent);
	menuItemAdd("Audio"   , curParent);
	menuItemAdd("Controls", curParent);

	fillMenuBack();

	for (int i = 0; i < menuItems.size(); i++) menuItems[i]->addToParent();
	switchMenu(menuItems[0]);
}
