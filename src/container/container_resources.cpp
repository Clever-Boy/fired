/***********************************************************************
     * File       : container_resources.cpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Resources
     * constructor

***********************************************************************/
fired::Resources::Resources() {
	sounds.explosion = new sf::SoundBuffer();
	sounds.thunder   = new sf::SoundBuffer();
	sounds.rain      = new sf::SoundBuffer();
	sounds.impact    = new sf::SoundBuffer();

	sounds.explosion->loadFromFile("data/snd/misc/explosion.wav");
	sounds.thunder->loadFromFile("data/snd/misc/thunder.wav");
	sounds.rain->loadFromFile("data/snd/misc/rain.wav");
	sounds.impact->loadFromFile("data/snd/misc/impact.wav");

	sounds.thunderSnd = new sf::Sound(*sounds.thunder);
	sounds.rainSnd    = new sf::Sound(*sounds.rain);
	sounds.impactSnd  = new sf::Sound(*sounds.impact);

	sounds.thunderSnd->setVolume(settings->volume.sound);
	sounds.rainSnd->setVolume(settings->volume.sound);
	sounds.impactSnd->setVolume(settings->volume.sound);

	sounds.rainSnd->setLoop(true);

	sounds.impactSnd->setMinDistance(SOUND_MINDISTANCE);
	sounds.impactSnd->setAttenuation(SOUND_ATTENUATION);



	win.trashTex  = new sf::Texture();
	win.emptyTex  = new sf::Texture();
	win.hoverTex  = new sf::Texture();
	win.normalTex = new sf::Texture();

	win.trashTex->loadFromFile("data/img/gui/inventory/trash.png");
	win.emptyTex->loadFromFile("data/img/gui/inventory/empty.png");
	win.hoverTex->loadFromFile("data/img/gui/inventory/hover.png");
	win.normalTex->loadFromFile("data/img/gui/inventory/normal.png");

	win.trashSpr = new sf::Sprite();
	win.emptySpr = new sf::Sprite();
	win.hoverSpr = new sf::Sprite();
	win.normalSpr = new sf::Sprite();

	win.trashSpr->setTexture(*win.trashTex);
	win.emptySpr->setTexture(*win.emptyTex);
	win.hoverSpr->setTexture(*win.hoverTex);
	win.normalSpr->setTexture(*win.normalTex);

	win.trashSpr->setOrigin(sf::Vector2f(win.trashTex->getSize())   / 2.0f);
	win.emptySpr->setOrigin(sf::Vector2f(win.emptyTex->getSize())   / 2.0f);
	win.hoverSpr->setOrigin(sf::Vector2f(win.hoverTex->getSize())   / 2.0f);
	win.normalSpr->setOrigin(sf::Vector2f(win.normalTex->getSize()) / 2.0f);



	sprites.coinTex      = new sf::Texture();
	sprites.smokeTex     = new sf::Texture();
	sprites.snowflakeTex = new sf::Texture();

	sprites.coinTex->loadFromFile("data/img/world/icons/misc/coin.png");
	sprites.smokeTex->loadFromFile("data/img/world/sprites/smoke.png");
	sprites.snowflakeTex->loadFromFile("data/img/world/sprites/snowflake.png");

	sprites.coin      = new sf::Sprite();
	sprites.smoke     = new sf::Sprite();
	sprites.snowflake = new sf::Sprite();

	sprites.coin->setTexture(*sprites.coinTex);
	sprites.smoke->setTexture(*sprites.smokeTex);
	sprites.snowflake->setTexture(*sprites.snowflakeTex);

	sprites.coin->setOrigin(sf::Vector2f(sprites.coinTex->getSize()) / 2.0f);
	sprites.smoke->setOrigin(sf::Vector2f(sprites.smokeTex->getSize()) / 2.0f);
	sprites.snowflake->setOrigin(sf::Vector2f(sprites.snowflakeTex->getSize()) / 2.0f);



	masks.bumpy = new sf::Texture();
	masks.flat  = new sf::Texture();

	masks.bumpy->loadFromFile("data/img/world/tileset/bumpy.png");
	masks.flat->loadFromFile("data/img/world/tileset/flat.png");



	progress.borderTex  = new sf::Texture();
	progress.emptyTex   = new sf::Texture();
	progress.fullTex    = new sf::Texture();

	progress.borderTex->loadFromFile("data/img/gui/progress/border.png");
	progress.emptyTex->loadFromFile("data/img/gui/progress/empty.png");
	progress.fullTex->loadFromFile("data/img/gui/progress/full.png");

	progress.emptyTex->setRepeated(true);
	progress.fullTex->setRepeated(true);

	progress.border = new sf::Sprite();
	progress.empty  = new sf::Sprite();
	progress.full   = new sf::Sprite();

	progress.border->setTexture(*progress.borderTex);
	progress.empty->setTexture(*progress.emptyTex);
	progress.full->setTexture(*progress.fullTex);

	progress.empty->setTextureRect(sf::IntRect(0, 0, PROGRESSBAR_WIDTH, PROGRESSBAR_HEIGHT));



	fonts.menu    = new sf::Font();
	fonts.game    = new sf::Font();
	fonts.credits = new sf::Font();
	fonts.loading = new sf::Font();

	fonts.menu->loadFromFile("data/fonts/monterey.ttf");
	fonts.game->loadFromFile("data/fonts/montserrat.ttf");
	fonts.credits->loadFromFile("data/fonts/mrsmonster.ttf");
	fonts.loading->loadFromFile("data/fonts/jennifer.ttf");
}



/***********************************************************************
     * Resources
     * destructor

***********************************************************************/
fired::Resources::~Resources() {
	delete sounds.explosion;
	delete sounds.thunder;
	delete sounds.rain;
	delete sounds.impact;

	delete sounds.thunderSnd;
	delete sounds.rainSnd;
	delete sounds.impactSnd;



	delete win.trashSpr;
	delete win.emptySpr;
	delete win.hoverSpr;
	delete win.normalSpr;

	delete win.trashTex;
	delete win.emptyTex;
	delete win.hoverTex;
	delete win.normalTex;



	delete sprites.coin;
	delete sprites.smoke;
	delete sprites.snowflake;

	delete sprites.coinTex;
	delete sprites.smokeTex;
	delete sprites.snowflakeTex;



	delete masks.flat;
	delete masks.bumpy;



	delete progress.border;
	delete progress.empty;
	delete progress.full;

	delete progress.borderTex;
	delete progress.emptyTex;
	delete progress.fullTex;



	delete fonts.menu;
	delete fonts.game;
	delete fonts.credits;
	delete fonts.loading;
}
