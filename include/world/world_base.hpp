/***********************************************************************
     * File       : world_base.hpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WORLD_BASE
#define __WORLD_BASE


namespace fired {
	struct World;


	enum WorldState {
		wsNormal,
		wsInventory,
		wsExchange,
		wsCharacter,
		wsMenu
	};
}


#include "world_sprite.hpp"
#include "world_explosion.hpp"
#include "particle.hpp"
#include "world_flytext.hpp"
#include "world_shot.hpp"
#include "world_sound.hpp"
#include "char.hpp"
#include "map.hpp"
#include "mapfile.hpp"
#include "world_gui.hpp"


namespace fired {
	struct World : GameScreen {
		fired::Map        *map;
		fired::Camera     *cam;
		fired::Crosshair  *crosshair;
		fired::Mouse      *mouse;
		fired::Player     *player;
		fired::GUI        *gui;

		fired::InventoryWindow  *inventoryWin;
		fired::ExchangeWindow   *exchangeWin;
		fired::CharacterWindow  *characterWin;
		fired::MenuWindow       *menuWin;

		fired::Timer creatureSpawnTimer;
		fired::Timer critterSpawnTimer;
		fired::Timer bossSpawnTimer;

		unsigned int      creatureSpawnMax;
		unsigned int      critterSpawnMax;
		unsigned int      bossSpawnMax;

		std::vector<fired::ParticleSystem*>  particles;
		std::vector<fired::Shot*>            shots;
		std::vector<fired::MeleeShot*>       meleeShots;
		std::vector<fired::BroadShot*>       broadShots;
		std::vector<fired::FlyText*>         texts;
		std::vector<fired::Chunk*>           chunks;
		std::vector<fired::CollectableItem*> items;
		std::vector<fired::Character*>       chars;
		std::vector<fired::Explosion*>       explosions;

		std::vector<fired::Creature*>        creatures;
		std::vector<fired::Creature*>        critters;
		std::vector<fired::Creature*>        bosses;

		bool              paused;
		fired::WorldState state;


		 World(fired::Mouse *_mouse);
		~World();

		void update();
		void processEvent(sf::Event event);

		void preUpdateState();
		void postUpdateState();
		void togglePause() { paused = !paused; };

		void checkShots();
		void checkPhys();
		void checkCreatures();
		void checkItems();
		void checkSpawns();
		void checkChunks();
		void checkPlayer();
		void checkParticles();
		void checkExplosions();
		void checkTexts();
		void checkLight();

		void interact(fired::Character *owner);
		void spawn(sf::Vector2f pos, fired::BaseCreature *creature, fired::MapSpawnType type);
		bool isCharExists(fired::Character *character);
		bool isSolidPixel(sf::Vector2f pixel)   { return map->isSolid(pixel.x / TILE_SIZE, pixel.y / TILE_SIZE); };
		bool isRectVisible(sf::FloatRect rect)  { return cam->isRectVisible(rect);                               };
		bool isPixelVisible(sf::Vector2f pixel) { return cam->isPixelVisible(pixel);                             };

		void addShot     (fired::Character *owner)                                                                     { shots.push_back(new fired::Shot(owner, this)); };
		void addBroadShot(sf::FloatRect _shot, sf::Vector2f _normal, fired::Character *_owner)                         { broadShots.push_back(new fired::BroadShot(_shot, _normal, _owner));       };
		void addMeleeShot(sf::Vector2f _pos, sf::Vector2f _direction, fired::Character *_owner)                        { meleeShots.push_back(new fired::MeleeShot(_pos, _direction, _owner));     };

		void addText        (sf::Vector2f pos, sf::Color color, int size, const char *text)                     { texts.push_back(new fired::FlyText(pos, color, size, text));                            };
		void addBulletSplash(sf::Vector2f pos, sf::Vector2f direction)                                          { particles.push_back(new fired::ParticleSystemSparc(pos, direction, this));              };
		void addBloodSplash (sf::Vector2f pos, sf::Vector2f direction, int bloodCount)                          { particles.push_back(new fired::ParticleSystemBlood(pos, direction, this, bloodCount)); };
		void addChunk       (fired::Bodypart *bodyPart, float scale, sf::Vector2f position, sf::Vector2f speed) { chunks.push_back(new fired::Chunk(bodyPart, scale, position, speed, this));             };
		void addItem        (fired::InventoryItem *item, sf::Vector2f pos, sf::Vector2f speed)                  { items.push_back(new fired::CollectableItem(item, pos, speed, this));                    };
		void addExplosion   (sf::Vector2f pos, float radius, float life, float knockback, int damage, fired::Character *owner, int fraction);
	};
}

#endif
