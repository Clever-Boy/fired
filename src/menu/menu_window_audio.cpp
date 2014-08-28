/***********************************************************************
     * File       : menu_window_audio.cpp
     * Created    : Aug 26, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MenuItemWindowAudio
     * constructor

***********************************************************************/
fired::MenuItemWindowAudio::MenuItemWindowAudio() : MenuItemWindow() {
	sf::Vector2f scrollSize(win->size.x - MENU_X_OFFSET * 2, 24);

	musicVolume = new fired::InputScroller(scrollSize, sf::Vector2f(MENU_X_OFFSET,  50), 0, 100, settings->volume.music, win);
	soundVolume = new fired::InputScroller(scrollSize, sf::Vector2f(MENU_X_OFFSET, 100), 0, 100, settings->volume.sound, win);
}



/***********************************************************************
     * MenuItemWindowAudio
     * destructor

***********************************************************************/
fired::MenuItemWindowAudio::~MenuItemWindowAudio() {
	delete musicVolume;
	delete soundVolume;
}



/***********************************************************************
     * MenuItemWindowAudio
     * update

***********************************************************************/
void fired::MenuItemWindowAudio::update() {
	render();

	musicVolume->update();
	soundVolume->update();
}



/***********************************************************************
     * MenuItemWindowAudio
     * render

***********************************************************************/
void fired::MenuItemWindowAudio::render() {
	win->render();
}



/***********************************************************************
     * MenuItemWindowAudio
     * click

***********************************************************************/
void fired::MenuItemWindowAudio::click(sf::Vector2f pos) {
	if (musicVolume->rect.contains(pos)) musicVolume->click(pos);
	if (soundVolume->rect.contains(pos)) soundVolume->click(pos);
}
