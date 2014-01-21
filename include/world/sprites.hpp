#ifndef __SPRITES
#define __SPRITES


namespace fired {
	struct GameSprite {
		sf::Sprite   *spr;
		sf::Texture  *tex;
		sf::Vector2f  size;


		 GameSprite(const char *filename);
		~GameSprite();
	};
}

#endif
