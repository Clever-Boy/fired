/***********************************************************************
     * File       : menu_base.cpp
     * Created    : Jul 18, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MainMenu
     * constructor

***********************************************************************/
fired::MainMenu::MainMenu(fired::Mouse *_mouse) {
	mouse    = _mouse;
	xOffset  = 0;

	game->setMusic("data/snd/themes/mainmenu.ogg");

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
	bgSprite->setSize(sf::Vector2f(settings->window.width, settings->window.height));

	menuItemTexture->loadFromFile("data/img/gui/mainmenu/menuitem.jpg");
	menuItemSprite->setTexture(*menuItemTexture);
	menuItemTexture->setSmooth(true);

	logoTexture->loadFromFile("data/img/gui/mainmenu/logo.png");
	logoSprite->setTexture(*logoTexture);
	logoTexture->setSmooth(true);

	if (logoTexture->getSize().x > settings->window.width)
		logoSprite->setScale((float)settings->window.width/logoTexture->getSize().x, (float)settings->window.width/logoTexture->getSize().x);
	else
		logoSprite->setPosition((settings->window.width - logoTexture->getSize().x) / 2, 0);

	menuCaption->setFont(*game->font);
	menuCaption->setCharacterSize(32);

	fillMenu();
	updateSettings();
}



/***********************************************************************
     * MainMenu
     * destructor

***********************************************************************/
fired::MainMenu::~MainMenu() {
	deleteList(menuItems);
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



/***********************************************************************
     * MainMenu
     * update

***********************************************************************/
void fired::MainMenu::update() {
	xOffset += frameClock * MENU_BG_SPEED;
	if (xOffset > bgTexture->getSize().x) xOffset -= bgTexture->getSize().x;

	processAnimation();
	render();
	for (unsigned int i = 0; i < currentMenu->subMenu.size(); i++) currentMenu->subMenu[i]->update();

	mouse->update();
}



/***********************************************************************
     * MainMenu
     * render

***********************************************************************/
void fired::MainMenu::render() {
	bgSprite->setTextureRect(sf::IntRect(xOffset, 0, settings->window.width, settings->window.height));
	app->draw(*bgSprite);
	app->draw(*logoSprite);
	app->draw(*menuCaption);
}



/***********************************************************************
     * MainMenu
     * processEvent

***********************************************************************/
void fired::MainMenu::processEvent(sf::Event event) {
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) click(mouse->pos);
}



/***********************************************************************
     * MainMenu
     * click

***********************************************************************/
void fired::MainMenu::click(sf::Vector2f pos) {
	if (animation != atNone) return;

	for (unsigned int i = 0; i < currentMenu->subMenu.size(); i++) 
		if (currentMenu->subMenu[i]->sprite->getLocalBounds().contains(pos - currentMenu->subMenu[i]->pos)) {
			clickSound->play();
			currentMenu->subMenu[i]->click();
		}
}



/***********************************************************************
     * MainMenu
     * updateSettings

***********************************************************************/
void fired::MainMenu::updateSettings() {
	clickSound->setVolume(settings->volume.sound);
}



/***********************************************************************
     * MainMenu
     * setNextMenu

***********************************************************************/
void fired::MainMenu::setNextMenu(fired::MenuItem *menuItem) {
	nextMenu = menuItem;
	initAnimation(atDown);
}



/***********************************************************************
     * MainMenu
     * switchMenu

***********************************************************************/
void fired::MainMenu::switchMenu(fired::MenuItem *menuItem) {
	currentMenu = menuItem;
	menuCaption->setString(*currentMenu->caption);
	menuCaption->setPosition(sf::Vector2f(MENU_X_OFFSET + (menuItemTexture->getSize().x - menuCaption->getGlobalBounds().width) / 2, MENU_Y_OFFSET));
	initAnimation(atUp);
}



/***********************************************************************
     * MainMenu
     * initAnimation

***********************************************************************/
void fired::MainMenu::initAnimation(fired::MenuAnimationType animType) {
	animation = animType;

	switch (animation) {
		case atNone:
			for (unsigned int i = 0; i < currentMenu->subMenu.size(); i++) {
				currentMenu->subMenu[i]->timeOffset = 0;
				currentMenu->subMenu[i]->yOffset = 0;
			}
			break;

		case atUp:
			for (unsigned int i = 0; i < currentMenu->subMenu.size(); i++) {
				currentMenu->subMenu[i]->timeOffset = -0.05 * i;
				currentMenu->subMenu[i]->yOffset = settings->window.height;
			}
			break;

		case atDown:
			for (unsigned int i = 0; i < currentMenu->subMenu.size(); i++) {
				currentMenu->subMenu[i]->timeOffset = -0.05 * (currentMenu->subMenu.size() - i - 1);
				currentMenu->subMenu[i]->yOffset = 0;
			}
			break;
	}
}



/***********************************************************************
     * MainMenu
     * processAnimation

***********************************************************************/
void fired::MainMenu::processAnimation() {
	switch (animation) {
		case atNone:
			break;

		case atUp:
			for (unsigned int i = 0; i < currentMenu->subMenu.size(); i++) {
				currentMenu->subMenu[i]->timeOffset += frameClock;
				if (currentMenu->subMenu[i]->timeOffset > 0)
					currentMenu->subMenu[i]->yOffset = 250.0 * exp(-currentMenu->subMenu[i]->timeOffset * 16.0 + 2.0) - 25.0;

				if (currentMenu->subMenu[i]->yOffset < 0)
					currentMenu->subMenu[i]->yOffset = 0;
			}

			if (currentMenu->subMenu[currentMenu->subMenu.size() - 1]->yOffset == 0) initAnimation(atNone);
			break;

		case atDown:
			for (unsigned int i = 0; i < currentMenu->subMenu.size(); i++) {
				currentMenu->subMenu[i]->timeOffset += frameClock;
				if (currentMenu->subMenu[i]->timeOffset > 0)
					currentMenu->subMenu[i]->yOffset = 15.0 * (exp(currentMenu->subMenu[i]->timeOffset * 12.0 + 2.0) - exp(2));
			}

			if (currentMenu->subMenu[0]->yOffset > settings->window.height) {
				switchMenu(nextMenu);
				initAnimation(atUp);
			}
			break;
	}
}



/***********************************************************************
     * MainMenu
     * menuItemAdd

***********************************************************************/
void fired::MainMenu::menuItemAdd(const char *_caption, fired::MenuItem *_parent, fired::MenuItemType itemType = itSubmenu, fired::Handler handlerFunc = NULL) {
	menuItems.push_back(new fired::MenuItem(this, menuItemSprite, _caption, _parent, itemType, handlerFunc));
}



/***********************************************************************
     * MainMenu
     * fillMenuBack

***********************************************************************/
void fired::MainMenu::fillMenuBack() {
	int menuItemCount = menuItems.size();
	for (int i = 1; i < menuItemCount; i++)
		if (menuItems[i]->itemType != itBack)
			menuItemAdd("Back", menuItems[i], itBack);
}



/***********************************************************************
     * MainMenu
     * fillMenu

***********************************************************************/
void fired::MainMenu::fillMenu() {
	fired::MenuItem *curParent;

	menuItemAdd("Main menu", NULL);

	curParent = menuItems[0];
	menuItemAdd("Start game", curParent);
	menuItemAdd("Options"   , curParent);
	menuItemAdd("Credits"   , curParent, itButton, &fired::Handlers::buttonCredits);
	menuItemAdd("Exit"      , curParent, itButton, &fired::Handlers::buttonExit);

	curParent = menuItems[2];
	menuItemAdd("Video"   , curParent);
	menuItemAdd("Audio"   , curParent);

	curParent = menuItems[1];
	menuItemAdd("Building" , curParent, itButton, &fired::Handlers::buttonStartBuilding);
	menuItemAdd("Mine"     , curParent, itButton, &fired::Handlers::buttonStartMine);
	menuItemAdd("Graveyard", curParent, itButton, &fired::Handlers::buttonStartGraveyard);

	fillMenuBack();

	for (unsigned int i = 0; i < menuItems.size(); i++) menuItems[i]->addToParent();
	switchMenu(menuItems[0]);
}
