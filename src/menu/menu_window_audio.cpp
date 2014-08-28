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
	musicVolume = new fired::InputScroller(sf::Vector2f(200, 32), sf::Vector2f(50,  50), 0, 100, 0, win);
	soundVolume = new fired::InputScroller(sf::Vector2f(200, 32), sf::Vector2f(50, 100), 0, 100, 0, win);
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
void fired::MenuItemWindowAudio::click(sf::Vector2f) {
}
