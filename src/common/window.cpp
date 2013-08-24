#include "game.hpp"

//======================================================================


fired::Window::Window(sf::Vector2f _size) {
	size = _size;
	offset = sf::Vector2f((settings->window.width - size.x) / 2.0f, (settings->window.height - size.y) / 2.0f);

	initPart(&windowTexBG, &windowSprBG, sf::Vector2i(size.x, size.y), "data/img/gui/window/window_main.tga");
	initPart(&windowTexL , &windowSprL , sf::Vector2i(6.0f  , size.y), "data/img/gui/window/window_left.tga");
	initPart(&windowTexR , &windowSprR , sf::Vector2i(6.0f  , size.y), "data/img/gui/window/window_right.tga");
	initPart(&windowTexT , &windowSprT , sf::Vector2i(size.x, 6.0f  ), "data/img/gui/window/window_top.tga");
	initPart(&windowTexB , &windowSprB , sf::Vector2i(size.x, 6.0f  ), "data/img/gui/window/window_bottom.tga");
	initPart(&windowTexLT, &windowSprLT, sf::Vector2i(6.0f  , 6.0f  ), "data/img/gui/window/window_corner_lt.tga");
	initPart(&windowTexRT, &windowSprRT, sf::Vector2i(6.0f  , 6.0f  ), "data/img/gui/window/window_corner_rt.tga");
	initPart(&windowTexLB, &windowSprLB, sf::Vector2i(6.0f  , 6.0f  ), "data/img/gui/window/window_corner_lb.tga");
	initPart(&windowTexRB, &windowSprRB, sf::Vector2i(6.0f  , 6.0f  ), "data/img/gui/window/window_corner_rb.tga");
}

//======================================================================


fired::Window::~Window() {
	delete windowSprBG;
	delete windowSprL;
	delete windowSprR;
	delete windowSprT;
	delete windowSprB;
	delete windowSprLT;
	delete windowSprRT;
	delete windowSprLB;
	delete windowSprRB;

	delete windowTexBG;
	delete windowTexL;
	delete windowTexR;
	delete windowTexT;
	delete windowTexB;
	delete windowTexLT;
	delete windowTexRT;
	delete windowTexLB;
	delete windowTexRB;
}

//======================================================================


void fired::Window::render() {
	return;
}

//======================================================================


void fired::Window::initPart(sf::Texture **tex, sf::RectangleShape **spr, sf::Vector2i _size, const char *texFile) {
	(*tex) = new sf::Texture();
	(*tex)->loadFromFile(texFile);
	(*tex)->setSmooth(true);
	(*tex)->setRepeated(true);

	(*spr) = new sf::RectangleShape(sf::Vector2f(_size));
	(*spr)->setTexture(*tex);
	(*spr)->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), _size));
}
