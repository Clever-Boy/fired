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
fired::Container::Container() {
	sqlite3 *db;
	sqlite3_open("data/database.sqlite", &db);

	loadContent(db, loadSprite   , "SELECT Path FROM Sprites");
	loadContent(db, loadSound    , "SELECT Name, Path FROM Sounds");
	loadContent(db, loadDecor    , "SELECT Decors.*, Sprites.ID FROM Decors, Sprites WHERE Sprites.Name = Decors.Sprite");
	loadContent(db, loadLight    , "SELECT LightSources.Name, LightSources.LightOffset, LightSources.Intensity, Decors.ID, LightSources.Color FROM LightSources, Decors WHERE LightSources.Decor = Decors.Name");
	loadContent(db, loadBodypart , "SELECT Bodyparts.Name, Bodyparts.BodypartType, Bodyparts.Origin, Sprites.ID FROM Bodyparts, Sprites WHERE Sprites.Name = Bodyparts.Sprite");
	loadContent(db, loadModel    , "SELECT * FROM Models");
	loadContent(db, loadArmor    , "SELECT Armors.ArmorType, Armors.Caption, Armors.Armor, Armors.Color, Bodyparts.ID, Armors.Extra, Armors.Name FROM Armors, Bodyparts WHERE Armors.ArmorType = Bodyparts.BodypartType AND Armors.Model = Bodyparts.Name");
	loadContent(db, loadWeapon   , "SELECT Weapons.*, Bodyparts.ID FROM Weapons LEFT OUTER JOIN Bodyparts ON Weapons.Model = Bodyparts.Name WHERE (Bodyparts.BodypartType = 'weapon' OR Bodyparts.ID is NULL)");
	loadContent(db, loadAmmo     , "SELECT Ammo.*, Sprites.ID FROM Ammo LEFT OUTER JOIN Sprites ON Ammo.Sprite = Sprites.Name");
	loadContent(db, loadItem     , "SELECT Items.*, Sprites.ID FROM Items, Sprites WHERE Sprites.Name = Items.Icon");
	loadContent(db, loadCreature , "SELECT Creatures.*, Models.ID, Weapons.ID, Ammo.ID FROM Creatures, Weapons, Models LEFT OUTER JOIN Ammo ON Creatures.Ammo = Ammo.Name WHERE Creatures.Model = Models.ModelName AND Creatures.Weapon = Weapons.Name");
	loadContent(db, loadTileset  , "SELECT Tiles.ID, Sprites.ID, Tiles.Flat, Tiles.Name FROM Tiles, Sprites WHERE Tiles.Sprite = Sprites.Name");
	loadContent(db, loadBiome    , "SELECT Biomes.ID, Biomes.Name, Biomes.Weather, Biomes.Lightness, Biomes.Background, Biomes.Creatures, Biomes.Intensity FROM Biomes");
	loadContent(db, loadExplosion, "SELECT * FROM Explosions");

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
