#include "game.hpp"
#include <fstream>
#include <string>

//======================================================================


void fired::CreditsScr::init(fired::Game *_game) {
	std::string line;
	std::ifstream creditsFile("data/img/gui/creditsscr/credits");
	int  iOffset;
	bool isCaption;

	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	yOffset  = 0;
	iOffset  = 100;

	game->setMusic("data/snd/themes/creditsscr.ogg");

	credits.push_back(new sf::Text);
	credits.back()->setFont(*game->getFont());
	credits.back()->setString(sf::String("F.I.R.E.D. v" PROJECT_VER " credits"));
	credits.back()->setCharacterSize(48);
	credits.back()->setStyle(sf::Text::Bold);
	credits.back()->setPosition((settings->window.width - credits.back()->getLocalBounds().width) / 2, settings->window.height);

	while(!creditsFile.eof()) {
		getline(creditsFile, line);
		iOffset += 50;
		if (line.length() == 0) continue;

		isCaption = line.find("$C") != -1;
		if (isCaption) line = line.substr(2);


		credits.push_back(new sf::Text);
		credits.back()->setFont(*game->getFont());
		credits.back()->setString(sf::String(line));

		if (isCaption) {
			credits.back()->setCharacterSize(36);
			credits.back()->setStyle(sf::Text::Bold);
			credits.back()->setPosition((settings->window.width - credits.back()->getLocalBounds().width) / 2, settings->window.height + iOffset);
			iOffset += 50;
		} else {
			credits.back()->setCharacterSize(24);
			credits.back()->setPosition((settings->window.width - CREDITSSCR_WIDTH) / 2, settings->window.height + iOffset);
		}
	}

	creditsFile.close();
}

//======================================================================


void fired::CreditsScr::deinit() {
	for (int i = 0; i < credits.size(); delete credits[i], i++);
	credits.clear();
}

//======================================================================


void fired::CreditsScr::update() {
	float yOffset = -frameClock * CREDITSSCR_SPEED;
	for (int i = 0; i < credits.size(); i++) credits[i]->move(0, yOffset);

	if (credits.back()->getGlobalBounds().top + credits.back()->getGlobalBounds().height < 0) 
		game->setGameState(gsMainMenu);

	render();
}

//======================================================================


void fired::CreditsScr::render() {
	for (int i = 0; i < credits.size(); i++) app->draw(*credits[i]);
}

//======================================================================


void fired::CreditsScr::processEvent(sf::Event event) {
	if ((event.type == sf::Event::MouseButtonReleased) || 
	    (event.type == sf::Event::KeyPressed))
		game->setGameState(gsMainMenu);
}
