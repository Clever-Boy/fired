#include "game.hpp"

void fired::MainMenu::init(fired::Game *_game) {
	bgTexture.loadFromFile("data/img/gui/mainmenu/bg.jpg");
	menuItemTexture.loadFromFile("data/img/gui/mainmenu/menuitem.jpg");
	logoTexture.loadFromFile("data/img/gui/mainmenu/logo.tga");

	menuItemSprite.setTexture(menuItemTexture);
	logoSprite.setTexture(logoTexture);
	bgSprite.setTexture(&bgTexture);

	bgTexture.setRepeated(true);
	bgSprite.setSize(sf::Vector2f(800,600));
	bgSprite.setTextureRect(sf::IntRect(0,0,800,600));

	game = _game;

	menuItem.init(game);
	return;
}


void fired::MainMenu::update(float frameClock) {
	render();
	return;
}


void fired::MainMenu::render() {
	game->app.draw(bgSprite);
}
