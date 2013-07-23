#include "game.hpp"

void fired::StartScr::init(fired::Game *_game) {
	game       = _game;
	timeOffset = 0;
	index      = 0;

	textures.push_back(new sf::Texture()); textures.back()->loadFromFile("data/img/startscr/01.jpg");
	textures.push_back(new sf::Texture()); textures.back()->loadFromFile("data/img/startscr/02.jpg");
	textures.push_back(new sf::Texture()); textures.back()->loadFromFile("data/img/startscr/03.jpg");


	for (int i = 0; i < textures.size(); i++) {
		sprites.push_back(new sf::Sprite());
		sprites[i]->setTexture(*textures[i]);
		sprites[i]->move((game->settings.window.width - textures[i]->getSize().x) / 2, (game->settings.window.height - textures[i]->getSize().y) / 2);
	}
}

void fired::StartScr::deinit() {
	for (int i = 0; i < textures.size(); free(sprites[i]), free(textures[i]), i++);
}

void fired::StartScr::update(float frameClock) {
	timeOffset += frameClock;
	if (timeOffset > STARTSCR_TIME_DELAY) {
		index++;
		timeOffset -= STARTSCR_TIME_DELAY;
	}

	if (index == sprites.size()) {
		game->setGameState(gsMainMenu);
		return;
	}

	if      (timeOffset < STARTSCR_TIME_APPEAR)    sprites[index]->setColor(sf::Color(255, 255, 255, 255 * timeOffset));
	else if (timeOffset < STARTSCR_TIME_DISAPPEAR) sprites[index]->setColor(sf::Color(255, 255, 255, 255));
	else                                           sprites[index]->setColor(sf::Color(255, 255, 255, 255 * (STARTSCR_TIME_DELAY - timeOffset)));

	render();
}


void fired::StartScr::render() {
	game->app.draw(*sprites[index]);
}


void fired::StartScr::processEvent(sf::Event event) {
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) click(sf::Mouse::getPosition(game->app));
}


void fired::StartScr::click(sf::Vector2i pos) {
	timeOffset = 0;
	index++;
}
