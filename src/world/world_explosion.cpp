/***********************************************************************
     * File       : world_explosion.cpp
     * Created    : Feb 05, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * BaseExplosion
     * constructor

***********************************************************************/
fired::BaseExplosion::BaseExplosion(const char *filename) {
	tex = new sf::Texture();
	tex->loadFromFile(filename);
	tex->setSmooth(true);

	sf::Vector2f origin(tex->getSize().y / 2, tex->getSize().y / 2);

	int step   = tex->getSize().y;
	int frames = (int)(tex->getSize().x / tex->getSize().y);
	radius     = tex->getSize().y / 2.0f;

	for (int i = 0; i < frames; i++) {
		spr.push_back(new sf::Sprite());
		spr[i]->setTexture(*tex);
		spr[i]->setOrigin(origin);
		spr[i]->setTextureRect(sf::IntRect(step * i, 0, step, tex->getSize().y));
	}
}



/***********************************************************************
     * BaseExplosion
     * destructor

***********************************************************************/
fired::BaseExplosion::~BaseExplosion() {
	deleteList(spr);
	delete tex;
}



/***********************************************************************
     * Explosion
     * constructor

***********************************************************************/
fired::Explosion::Explosion(sf::Vector2f _pos, float radius, float _life) {
	base     = container->getExplosion();
	pos      = _pos;
	life     = _life;
	lifetime = _life;
	scale    = sf::Vector2f(radius / base->radius, radius / base->radius);
	sound    = new sf::Sound(*resources->sounds.explosion);

	sound->setVolume(settings->volume.sound);
	sound->setMinDistance(SOUND_MINDISTANCE);
	sound->setAttenuation(SOUND_ATTENUATION);
	sound->setPosition(pos.x, pos.y, 0.0f);
	sound->play();
}



/***********************************************************************
     * Explosion
     * destructor

***********************************************************************/
fired::Explosion::~Explosion() {
	sound->stop();
	delete sound;
}



/***********************************************************************
     * Explosion
     * update

***********************************************************************/
bool fired::Explosion::update() {
	if ((life -= frameClock) > 0.0f)   render();
	else if (sound->getStatus() == sf::Sound::Stopped) return false;

	return true;
}



/***********************************************************************
     * Explosion
     * render

***********************************************************************/
void fired::Explosion::render() {
	int frame = (int)((lifetime - life) * (base->spr.size() - 1) / lifetime);
	sf::Sprite *spr = base->spr[frame];

	spr->setScale(scale);
	spr->setPosition(pos);
	app->draw(*spr);
}
