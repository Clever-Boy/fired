/***********************************************************************
     * File       : win_menu.cpp
     * Created    : Aug 28, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MenuWindow
     * constructor

***********************************************************************/
fired::MenuWindow::MenuWindow(fired::World *_world) {
	world  = _world;
	win    = new fired::Window(sf::Vector2f(200, 190));

	text = new sf::Text();
	text->setFont(*resources->fonts.game);
	text->setCharacterSize(16);
	text->setPosition(win->offset + sf::Vector2f(30.0f, 360.0f));
	text->setColor(sf::Color::White);

	button = new sf::RectangleShape(sf::Vector2f(180, 30));
	button->setOutlineThickness(2);
	button->setOutlineColor(sf::Color(44, 88, 22));
}



/***********************************************************************
     * MenuWindow
     * destructor

***********************************************************************/
fired::MenuWindow::~MenuWindow() {
	delete win;
	delete text;
	delete button;
}



/***********************************************************************
     * MenuWindow
     * update

***********************************************************************/
void fired::MenuWindow::update(sf::Vector2f mousePos) {
	render(mousePos);
}



/***********************************************************************
     * MenuWindow
     * renderButton

***********************************************************************/
void fired::MenuWindow::renderButton(float y, const char *caption, sf::Vector2f mousePos) {
	if (sf::FloatRect(win->offset + sf::Vector2f(10, y), sf::Vector2f(180, 30)).contains(mousePos))
		button->setFillColor(sf::Color(100, 100, 100, 200));
	else
		button->setFillColor(sf::Color(0, 0, 0, 200));

	button->setPosition(win->offset + sf::Vector2f(10, y));
	app->draw(*button);

	text->setString(sf::String(caption));
	text->setPosition(win->offset + sf::Vector2f(100 - text->getGlobalBounds().width / 2, y + 15 - text->getGlobalBounds().height / 2));
	app->draw(*text);
}



/***********************************************************************
     * MenuWindow
     * render

***********************************************************************/
void fired::MenuWindow::render(sf::Vector2f mousePos) {
	win->render();

	text->setString(sf::String("Main Menu"));
	text->setPosition(win->offset + sf::Vector2f(100 - text->getGlobalBounds().width / 2, 10));
	app->draw(*text);

	renderButton(70.0f , "Back to game", mousePos);
	renderButton(110.0f, "Exit to Menu", mousePos);
	renderButton(150.0f, "Exit"        , mousePos);
}



/***********************************************************************
     * MenuWindow
     * click

***********************************************************************/
void fired::MenuWindow::click(sf::Vector2f mousePos) {
	if (sf::FloatRect(win->offset + sf::Vector2f(10, 70 ), sf::Vector2f(180, 30)).contains(mousePos)) world->state = wsNormal;
	if (sf::FloatRect(win->offset + sf::Vector2f(10, 110), sf::Vector2f(180, 30)).contains(mousePos)) game->setGameState(gsMainMenu);
	if (sf::FloatRect(win->offset + sf::Vector2f(10, 150), sf::Vector2f(180, 30)).contains(mousePos)) game->stop();
}
