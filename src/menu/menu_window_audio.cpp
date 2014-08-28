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
}



/***********************************************************************
     * MenuItemWindowAudio
     * destructor

***********************************************************************/
fired::MenuItemWindowAudio::~MenuItemWindowAudio() {
}



/***********************************************************************
     * MenuItemWindowAudio
     * update

***********************************************************************/
void fired::MenuItemWindowAudio::update() {
	render();
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
