#ifndef __TILESET
#define __TILESET


namespace fired {
	struct Tileset {
		sf::Texture *maskTex;
		std::vector<sf::Texture*> textures;
		std::vector<sf::Sprite*>  sprites;


		 Tileset();
		~Tileset();

		void addTile(const char *filename);
	};
}

#endif
