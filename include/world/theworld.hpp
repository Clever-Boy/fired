#ifndef __THEWORLD
#define __THEWORLD


namespace fired {
	class World;


	enum WorldState {
		wsNormal,
		wsInventory,
		wsExchange
	};
}


#include "particle.hpp"
#include "flytext.hpp"
#include "weapon.hpp"
#include "shot.hpp"
#include "char.hpp"
#include "container.hpp"
#include "map.hpp"
#include "gui.hpp"


namespace fired {
	class World : public GameScreen {
	private:
		fired::Map       *map;
		fired::Camera    *cam;
		fired::Crosshair *crosshair;
		fired::Mouse     *mouse;
		fired::Player    *player;
		fired::GUI       *gui;
		fired::Container *container;

		fired::InventoryWindow *inventoryWin;
		fired::ExchangeWindow  *exchangeWin;

		std::vector<fired::ParticleSystem*>  particles;
		std::vector<fired::Shot*>            shots;
		std::vector<fired::MeleeShot*>       meleeShots;
		std::vector<fired::BroadShot*>       broadShots;
		std::vector<fired::Creature*>        creatures;
		std::vector<fired::FlyText*>         texts;
		std::vector<fired::Chunk*>           chunks;
		std::vector<fired::CollectableItem*> items;


		bool paused;
		fired::WorldState state;


	public:
		 World(fired::Mouse *_mouse);
		~World();

		std::vector<fired::Character*> chars;


		void update();
		void processEvent(sf::Event event);

		void preUpdateState();
		void postUpdateState();
		void setState(fired::WorldState newState) {state = newState; };

		void checkShots();
		void checkPhys();
		void checkCreatures();
		void checkItems();


		void spawn(sf::Vector2f pos, const char *creature);
		bool isCharExists(fired::Character *character);
		bool isSolidPixel(sf::Vector2f pixel)  {return map->isSolid(pixel.x / TILE_SIZE, pixel.y / TILE_SIZE); };
		bool isRectVisible(sf::FloatRect rect) {return cam->isRectVisible(rect); };


		void addShot     (sf::Vector2f pos, float angle, float speed, fired::Character *owner, sf::Sprite *sprite) { shots.push_back(new fired::Shot(pos, angle, speed, owner, sprite)); };
		void addBroadShot(sf::FloatRect _shot, sf::Vector2f _normal, fired::Character *_owner)                     { broadShots.push_back(new fired::BroadShot(_shot, _normal, _owner)); };
		void addMeleeShot(sf::Vector2f _pos, sf::Vector2f _direction, fired::Character *_owner)                    { meleeShots.push_back(new fired::MeleeShot(_pos, _direction, _owner)); };


		void addText        (sf::Vector2f pos, sf::Color color, int size, const char *text)                     {texts.push_back(new fired::FlyText(pos, color, size, text)); };
		void addBulletSplash(sf::Vector2f pos, sf::Vector2f direction)                                          {particles.push_back(new fired::ParticleSystemSplash(pos, direction, this, sf::Color(239, 231, 145, 255), 2, 20, 0.3, 0, false)); };
		void addBloodSplash (sf::Vector2f pos, sf::Vector2f direction, int bloodCount)                          {particles.push_back(new fired::ParticleSystemSplash(pos, direction, this, sf::Color(150, 0, 0, 155), 7, bloodCount, 17.0, 0.5, true)); };
		void addChunk       (fired::Bodypart *bodyPart, float scale, sf::Vector2f position, sf::Vector2f speed) {chunks.push_back(new fired::Chunk(bodyPart, scale, position, speed)); };
		void addItem        (fired::InventoryItem *item, sf::Vector2f pos, sf::Vector2f speed)                  {items.push_back(new fired::CollectableItem(item, pos, speed)); };


		fired::BaseWeapon   *getWeapon  (const char *name)                           {return container->getWeapon(name); };
		fired::BaseBodypart *getBodypart(const char *name, fired::BodypartType type) {return container->getBodypart(name, type); };
		fired::BaseModel    *getModel   (const char *name)                           {return container->getModel(name); };
		fired::BaseCreature *getCreature(const char *name)                           {return container->getCreature(name); };
		fired::BaseAI       *getAI      (const char *name, fired::Creature* owner)   {return container->getAI(name, owner); };
		fired::BaseDecor    *getDecor   (const char *name)                           {return container->getDecor(name); };
		sf::Sprite          *getSprite  (const char *name)                           {return container->getSprite(name); };


		void togglePause() {paused = !paused; };
		void interact(fired::Character *owner);
	};
}

#endif
