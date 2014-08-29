/***********************************************************************
     * File       : menu_window_video.cpp
     * Created    : Aug 26, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MenuItemWindowVideo
     * constructor

***********************************************************************/
fired::MenuItemWindowVideo::MenuItemWindowVideo() : MenuItemWindow() {
	modes      = new fired::InputList(win->size.x - MENU_X_OFFSET * 2, sf::Vector2f(MENU_X_OFFSET, 50), 2, win);
	fullscreen = new fired::InputCheckbox(sf::Vector2f(MENU_X_OFFSET, 170), settings->window.fullScreen, win);
	apply      = new fired::InputButton(sf::Vector2f(150, 32), sf::Vector2f(win->size.x / 2.0f - 75, 200), "Apply", win);

	videoModeList(&modes->list);
	win->text->setCharacterSize(16);

	char curMode[128];
	snprintf(curMode, sizeof(curMode), "%d x %d x %dbpp", settings->window.width, settings->window.height, settings->window.bpp);
	modes->setSelected(curMode);
}



/***********************************************************************
     * MenuItemWindowVideo
     * destructor

***********************************************************************/
fired::MenuItemWindowVideo::~MenuItemWindowVideo() {
	delete fullscreen;
	delete modes;
	delete apply;
}



/***********************************************************************
     * MenuItemWindowVideo
     * update

***********************************************************************/
void fired::MenuItemWindowVideo::update() {
	render();

	modes->update();
	fullscreen->update();
	apply->update();
}



/***********************************************************************
     * MenuItemWindowVideo
     * render

***********************************************************************/
void fired::MenuItemWindowVideo::render() {
	win->render();
	win->renderText(MENU_X_OFFSET + 20, 170, "Fullscreen", taLeft);
}



/***********************************************************************
     * MenuItemWindowVideo
     * applyVideoSettings

***********************************************************************/
void fired::MenuItemWindowVideo::applyVideoSettings() {
	MenuItemWindow::applyVideoSettings();

	modes->setSize(win->size.x - MENU_X_OFFSET * 2);
	apply->setPosition(sf::Vector2f(win->size.x / 2.0f - 75, 200));
}



/***********************************************************************
     * MenuItemWindowVideo
     * click

***********************************************************************/
bool fired::MenuItemWindowVideo::click(sf::Vector2f pos) {
	if (modes->rect.contains(pos)) {
		modes->click(pos);
		return true;
	}

	if (fullscreen->rect.contains(pos)) {
		fullscreen->click();
		return true;
	}

	if (apply->rect.contains(pos)) {
		sscanf(modes->getSelected(), "%d x %d x %dbpp", &settings->window.width, &settings->window.height, &settings->window.bpp);
		settings->window.fullScreen = fullscreen->val;

		game->applyVideoSettings();
		return true;
	}

	return false;
}
