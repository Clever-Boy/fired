#include "game.hpp"
#include <fstream>
#include <string>

void fired::CreditsScr::init(fired::Game *_game) {
	std::string line;
	std::ifstream creditsFile("data/img/creditsscr/credits");
	int  iOffset;
	bool isCaption;

	game    = _game;
	yOffset = 0;
	iOffset = 100;

	musicTheme = new sf::Music();
	musicTheme->openFromFile("data/snd/themes/creditsscr.ogg");
	musicTheme->setLoop(true);
	musicTheme->play();

	credits.push_back(new sf::Text);
	credits.back()->setFont(game->font);
	credits.back()->setString(sf::String("F.I.R.E.D. v" PROJECT_VER " credits"));
	credits.back()->setCharacterSize(96);
	credits.back()->setStyle(sf::Text::Bold);
	credits.back()->setPosition((game->settings.window.width - credits.back()->getLocalBounds().width) / 2, game->settings.window.height);

	while(!creditsFile.eof()) {
		getline(creditsFile, line);
		iOffset += 50;
		if (line.length() == 0) continue;

		isCaption = line.find("$C") != -1;
		if (isCaption) line = line.substr(2);


		credits.push_back(new sf::Text);
		credits.back()->setFont(game->font);
		credits.back()->setString(sf::String(line));

		if (isCaption) {
			credits.back()->setCharacterSize(72);
			credits.back()->setStyle(sf::Text::Bold);
			credits.back()->setPosition((game->settings.window.width - credits.back()->getLocalBounds().width) / 2, game->settings.window.height + iOffset);
			iOffset += 50;
		} else {
			credits.back()->setCharacterSize(48);
			credits.back()->setPosition((game->settings.window.width - CREDITSSCR_WIDTH) / 2, game->settings.window.height + iOffset);
		}
	}

	creditsFile.close();
}


void fired::CreditsScr::deinit() {
	for (int i = 0; i < credits.size(); delete credits[i], i++);
	credits.clear();

	musicTheme->stop();
	delete musicTheme;
}


void fired::CreditsScr::update(float frameClock) {
	float yOffset = -frameClock * CREDITSSCR_SPEED;
	for (int i = 0; i < credits.size(); i++) credits[i]->move(0, yOffset);

	if (credits.back()->getGlobalBounds().top + credits.back()->getGlobalBounds().height < 0) 
		game->setGameState(gsMainMenu);

	render();
}


void fired::CreditsScr::render() {
	for (int i = 0; i < credits.size(); i++) game->app.draw(*credits[i]);
}


void fired::CreditsScr::processEvent(sf::Event event) {
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) game->setGameState(gsMainMenu);
	if (event.type == sf::Event::KeyPressed) game->setGameState(gsMainMenu);
}
