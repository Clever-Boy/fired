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
	musicVolume = new fired::InputScroller(sf::Vector2f(200, 32), sf::Vector2f(50,  50), 0, 100, settings->volume.music, win);
	soundVolume = new fired::InputScroller(sf::Vector2f(200, 32), sf::Vector2f(50, 100), 0, 100, settings->volume.sound, win);
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
