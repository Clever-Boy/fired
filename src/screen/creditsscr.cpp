/***********************************************************************
     * File       : creditsscr.cpp
     * Created    : Jul 22, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * CreditsScr
     * constructor

***********************************************************************/
fired::CreditsScr::CreditsScr() {
	std::string line;
	std::ifstream creditsFile("data/img/gui/creditsscr/credits");
	int  iOffset;
	bool isCaption;

	yOffset  = 0;
	iOffset  = 100;

	game->setMusic("data/snd/themes/creditsscr.ogg");

	credits.push_back(new sf::Text);
	credits.back()->setFont(*game->font);
	credits.back()->setString(sf::String(PROJECT_CAPTION " v" PROJECT_VER " credits"));
	credits.back()->setCharacterSize(48);
	credits.back()->setStyle(sf::Text::Bold);
	credits.back()->setPosition((settings->window.width - credits.back()->getLocalBounds().width) / 2, settings->window.height);

	while(!creditsFile.eof()) {
		getline(creditsFile, line);
		iOffset += 50;
		if (line.length() == 0) continue;

		isCaption = (line.find("$C") != std::string::npos);
		if (isCaption) line = line.substr(2);


		credits.push_back(new sf::Text);
		credits.back()->setFont(*game->font);
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



/***********************************************************************
     * CreditsScr
     * destructor

***********************************************************************/
fired::CreditsScr::~CreditsScr() {
	deleteList(credits);
}



/***********************************************************************
     * CreditsScr
     * update

***********************************************************************/
void fired::CreditsScr::update() {
	float yOffset = -frameClock * CREDITSSCR_SPEED;
	for (unsigned int i = 0; i < credits.size(); i++) credits[i]->move(0, yOffset);

	if (credits.back()->getGlobalBounds().top + credits.back()->getGlobalBounds().height < 0) 
		game->setGameState(gsMainMenu);

	render();
}



/***********************************************************************
     * CreditsScr
     * render

***********************************************************************/
void fired::CreditsScr::render() {
	for (unsigned int i = 0; i < credits.size(); i++) app->draw(*credits[i]);
}



/***********************************************************************
     * CreditsScr
     * processEvent

***********************************************************************/
void fired::CreditsScr::processEvent(sf::Event event) {
	if ((event.type == sf::Event::MouseButtonReleased) || 
	    (event.type == sf::Event::KeyPressed))
		game->setGameState(gsMainMenu);
}
