/***********************************************************************
     * File       : theworld.hpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __THEWORLD
#define __THEWORLD


namespace fired {
	struct World;


	enum WorldState {
		wsNormal,
		wsInventory,
		wsExchange,
		wsCharacter
	};
}


#include "sprites.hpp"
#include "particle.hpp"
#include "flytext.hpp"
#include "shot.hpp"
#include "char.hpp"
#include "container.hpp"
#include "map.hpp"
#include "gui.hpp"


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

		std::vector<fired::ParticleSystem*>  particles;
		std::vector<fired::Shot*>            shots;
		std::vector<fired::MeleeShot*>       meleeShots;
		std::vector<fired::BroadShot*>       broadShots;
		std::vector<fired::Creature*>        creatures;
		std::vector<fired::FlyText*>         texts;
		std::vector<fired::Chunk*>           chunks;
		std::vector<fired::CollectableItem*> items;
		std::vector<fired::Character*>       chars;

		bool paused;
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

		void interact(fired::Character *owner);
		void spawn(sf::Vector2f pos, const char *creature);
		bool isCharExists(fired::Character *character);
		bool isSolidPixel(sf::Vector2f pixel)   { return map->isSolid(pixel.x / TILE_SIZE, pixel.y / TILE_SIZE); };
		bool isRectVisible(sf::FloatRect rect)  { return cam->isRectVisible(rect);                               };
		bool isPixelVisible(sf::Vector2f pixel) { return cam->isPixelVisible(pixel);                             };

		void addShot     (sf::Vector2f pos, float angle, float speed, fired::Character *owner, fired::GameSprite *sprite) { shots.push_back(new fired::Shot(pos, angle, speed, owner, sprite, this)); };
		void addBroadShot(sf::FloatRect _shot, sf::Vector2f _normal, fired::Character *_owner)                         { broadShots.push_back(new fired::BroadShot(_shot, _normal, _owner));       };
		void addMeleeShot(sf::Vector2f _pos, sf::Vector2f _direction, fired::Character *_owner)                        { meleeShots.push_back(new fired::MeleeShot(_pos, _direction, _owner));     };

		void addText        (sf::Vector2f pos, sf::Color color, int size, const char *text)                     { texts.push_back(new fired::FlyText(pos, color, size, text));                                                                           };
		void addBulletSplash(sf::Vector2f pos, sf::Vector2f direction)                                          { particles.push_back(new fired::ParticleSystemSplash(pos, direction, this, sf::Color(239, 231, 145, 255), 2, 20, 0.3, 0, false));       };
		void addBloodSplash (sf::Vector2f pos, sf::Vector2f direction, int bloodCount)                          { particles.push_back(new fired::ParticleSystemSplash(pos, direction, this, sf::Color(150, 0, 0, 155), 3, bloodCount, 17.0, 0.5, true)); };
		void addChunk       (fired::Bodypart *bodyPart, float scale, sf::Vector2f position, sf::Vector2f speed) { chunks.push_back(new fired::Chunk(bodyPart, scale, position, speed, this));                                                            };
		void addItem        (fired::InventoryItem *item, sf::Vector2f pos, sf::Vector2f speed)                  { items.push_back(new fired::CollectableItem(item, pos, speed, this));                                                                   };
	};
}

#endif
