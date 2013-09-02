#ifndef __DECOR
#define __DECOR


namespace fired {
	struct MapDecor {
		char name[64];
		sf::Vector2f pos;


		MapDecor() {};
		MapDecor(const char *_name, sf::Vector2f _pos);
	};

/*--------------------------------------------------------------------*/

	struct BaseDecor {
		char name[64];
		sf::Texture *tex;
		sf::Sprite  *spr;
		sf::Vector2f size;


		 BaseDecor(const char *_name, const char *filename);
		~BaseDecor();
	};

/*--------------------------------------------------------------------*/

	struct Decor {
		char name[64];
		sf::Vector2f  pos;
		sf::FloatRect rect;
		sf::Sprite   *sprite;
		sf::Color     color;


		Decor(fired::BaseDecor *base, sf::Vector2f _pos);
		void render();
	};
}

#endif
