/***********************************************************************
     * File       : container_base.cpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Container
     * constructor

***********************************************************************/
fired::Container::Container(fired::LoadingScr *_screen) {
	screen = _screen;
	screen->mainBar->setLimit(14);
	screen->mainBar->reset();

	sqlite3 *db;
	sqlite3_open("data/database.sqlite", &db);

	loadContent(db, "sprites"   , loadSprite   , "SELECT Path FROM Sprites");
	loadContent(db, "sounds"    , loadSound    , "SELECT Name, Path FROM Sounds");
	loadContent(db, "decors"    , loadDecor    , "SELECT Decors.*, Sprites.ID FROM Decors, Sprites WHERE Sprites.Name = Decors.Sprite");
	loadContent(db, "lights"    , loadLight    , "SELECT LightSources.Name, LightSources.LightOffset, LightSources.Intensity, Decors.ID, LightSources.Color FROM LightSources, Decors WHERE LightSources.Decor = Decors.Name");
	loadContent(db, "bodyparts" , loadBodypart , "SELECT Bodyparts.Name, Bodyparts.BodypartType, Bodyparts.Origin, Sprites.ID FROM Bodyparts, Sprites WHERE Sprites.Name = Bodyparts.Sprite");
	loadContent(db, "models"    , loadModel    , "SELECT * FROM Models");
	loadContent(db, "armors"    , loadArmor    , "SELECT Armors.ArmorType, Armors.Caption, Armors.Armor, Armors.Color, Bodyparts.ID, Armors.Extra, Armors.Name FROM Armors, Bodyparts WHERE Armors.ArmorType = Bodyparts.BodypartType AND Armors.Model = Bodyparts.Name");
	loadContent(db, "weapons"   , loadWeapon   , "SELECT Weapons.*, Bodyparts.ID FROM Weapons LEFT OUTER JOIN Bodyparts ON Weapons.Model = Bodyparts.Name WHERE (Bodyparts.BodypartType = 'weapon' OR Bodyparts.ID is NULL)");
	loadContent(db, "ammo"      , loadAmmo     , "SELECT Ammo.*, Sprites.ID FROM Ammo LEFT OUTER JOIN Sprites ON Ammo.Sprite = Sprites.Name");
	loadContent(db, "items"     , loadItem     , "SELECT Items.*, Sprites.ID FROM Items, Sprites WHERE Sprites.Name = Items.Icon");
	loadContent(db, "creatures" , loadCreature , "SELECT Creatures.*, Models.ID, Weapons.ID, Ammo.ID FROM Creatures, Weapons, Models LEFT OUTER JOIN Ammo ON Creatures.Ammo = Ammo.Name WHERE Creatures.Model = Models.ModelName AND Creatures.Weapon = Weapons.Name");
	loadContent(db, "tilesets"  , loadTileset  , "SELECT Tiles.ID, Sprites.ID, Tiles.Flat, Tiles.Name FROM Tiles, Sprites WHERE Tiles.Sprite = Sprites.Name");
	loadContent(db, "biomes"    , loadBiome    , "SELECT Biomes.ID, Biomes.Name, Biomes.Weather, Biomes.Lightness, Biomes.Background, Biomes.Creatures, Biomes.Intensity FROM Biomes");
	loadContent(db, "explosions", loadExplosion, "SELECT * FROM Explosions");

	sqlite3_close(db);
}



/***********************************************************************
     * Container
     * destructor

***********************************************************************/
fired::Container::~Container() {
	deleteList(biomes);
	deleteList(tilesets);
	deleteList(items);
	deleteList(ammos);
	deleteList(weapons);
	deleteList(armors);
	deleteList(bodyparts);
	deleteList(models);
	deleteList(creatures);
	deleteList(decors);
	deleteList(sprites);
	deleteList(sounds);
	deleteList(explosions);
}
