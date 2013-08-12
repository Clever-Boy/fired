#include "game.hpp"

//======================================================================


fired::Mouse::Mouse() {
	mouseTex = new sf::Texture();
	mouseCur = new sf::Sprite();

	mouseTex->loadFromFile("data/img/gui/mainmenu/mouse.tga");
	mouseCur->setTexture(*mouseTex);
	mouseTex->setSmooth(true);
}

//======================================================================


fired::Mouse::~Mouse() {
	delete mouseTex;
	delete mouseCur;
}

//======================================================================


void fired::Mouse::update() {
	pos = sf::Vector2f(sf::Mouse::getPosition(*app));
	render();
}

//======================================================================


void fired::Mouse::render() {
	mouseCur->setPosition(pos);
	app->draw(*mouseCur);
}
