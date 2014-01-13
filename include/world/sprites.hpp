#ifndef __SPRITES
#define __SPRITES


namespace fired {
	struct GameSprite {
		char         name[64];
		sf::Sprite  *spr;
		sf::Texture *tex;


		 GameSprite(const char *_name, const char *filename);
		~GameSprite();
	};

	struct NewGameSprite {
		sf::Sprite  *spr;
		sf::Texture *tex;


		 NewGameSprite(const char *filename);
		~NewGameSprite();
	};
}

#endif
