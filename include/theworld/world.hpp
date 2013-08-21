#ifndef __WORLD
#define __WORLD


#include <SFML/Graphics.hpp>
#include "char.hpp"
#include "map.hpp"
#include "prototypes.hpp"
#include "particle.hpp"
#include "theworld.hpp"


namespace fired {
	class World : public GameScreen {
	private:
		fired::Map       *map;
		fired::Camera    *cam;
		fired::Player    *player;
		fired::GUI       *gui;
		fired::Container *container;

		std::vector<fired::ParticleSystem*>  particles;
		std::vector<fired::Shot*>            shots;
		std::vector<fired::MeleeShot*>       meleeShots;
		std::vector<fired::BroadShot*>       broadShots;
		std::vector<fired::Creature*>        creatures;
		std::vector<fired::FlyText*>         texts;
		std::vector<fired::Chunk*>           chunks;
		std::vector<fired::CollectableItem*> items;


	public:
		 World();
		~World();

		std::vector<fired::Character*> chars;

		void update();

		void processEvent(sf::Event event);
		void checkControls();
		void checkShots();
		void checkPhys(fired::Character *character) {map->checkPhys(character); };

		void spawn(sf::Vector2f pos, const char *creature);
		bool isSolidPixel(sf::Vector2f pixel) {return map->isSolid(pixel.x / TILE_SIZE, pixel.y / TILE_SIZE); };
		bool isCharExists(fired::Character *character);

		void addShot(sf::Vector2f pos, float angle, float speed, fired::Character *owner, sf::Sprite *sprite);
		void addBroadShot(sf::FloatRect _shot, sf::Vector2f _normal, fired::Character *_owner);
		void addMeleeShot(sf::Vector2f _pos, sf::Vector2f _direction, fired::Character *_owner);

		void addText(sf::Vector2f pos, sf::Color color, int size, const char *text);
		void addBulletSplash(sf::Vector2f pos, sf::Vector2f direction);
		void addBloodSplash(sf::Vector2f pos, sf::Vector2f direction, int bloodCount);
		void addChunk(fired::Bodypart *bodyPart, float scale, sf::Vector2f position, sf::Vector2f speed);

		fired::BaseWeapon   *getWeapon(const char *name) {return container->getWeapon(name); };
		fired::BaseBodypart *getBodypart(const char *name, fired::BodypartType type) {return container->getBodypart(name, type); };
		fired::BaseModel    *getModel(const char *name) {return container->getModel(name); };
		fired::BaseCreature *getCreature(const char *name) {return container->getCreature(name); };
		fired::BaseAI       *getAI(const char *name, fired::Creature* owner) {return container->getAI(name, owner); };
		fired::BaseDecor    *getDecor(const char *name) {return container->getDecor(name); };
		sf::Sprite          *getSprite(const char *name) {return container->getSprite(name); };
	};
}

#endif
