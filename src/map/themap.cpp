#include "game.hpp"


void fired::Map::init(fired::Game *_game, fired::Camera *_cam, b2World *_physWorld) {
	game      = _game;
	settings  = game->getSettings();
	app       = game->getApp();
	cam       = _cam;
	physWorld = _physWorld;

	bgTex    = new sf::Texture();
	bgSprite = new sf::RectangleShape();

	bgTex->loadFromFile("data/img/bg/sky.jpg");
	bgSprite->setTexture(bgTex);
	bgTex->setRepeated(true);
	bgSprite->setSize(sf::Vector2f(settings->window.width, settings->window.height));

	tileset.init("data/img/tilesets/dirt.tga");

	visibleTiles.x = settings->window.width  / TILE_SIZE + 2;
	visibleTiles.y = settings->window.height / TILE_SIZE + 2;


	for (int i = 0; i < 200; i++) for (int j = 0; j < 200; j++) {
		tiles[i][j].init(NULL, i, j);
	}

	// Test map generation
	for (int i = 0; i < 19; i++) 
		for (int j = 0; j < 200; j++) {
			tiles[i][j].init(&tileset, i, j);
			tiles[j][199-i].init(&tileset, j, 199-i);
			tiles[199-i][j].init(&tileset, 199-i, j);
		}

	for (int j = 0; j < 200; j+=2) tiles[20][j].init(&tileset, 20, j);
	for (int i = 0; i < 50; i+=2) tiles[i][29].init(&tileset, i, 29);

	for (int i = 65; i < 200; i++) tiles[i][180].init(&tileset, i, 180);
	for (int i = 75; i < 200; i++) tiles[i][179].init(&tileset, i, 179);
	
	for (int i = 100; i < 200; i++) tiles[i][178].init(&tileset, i, 178);
	for (int i = 100; i < 200; i++) tiles[i][177].init(&tileset, i, 177);

	for (int i = 125; i < 200; i++) tiles[i][176].init(&tileset, i, 176);
	for (int i = 125; i < 200; i++) tiles[i][175].init(&tileset, i, 175);
	for (int i = 125; i < 200; i++) tiles[i][174].init(&tileset, i, 174);
	
	for (int i = 150; i < 200; i++) tiles[i][173].init(&tileset, i, 173);
	for (int i = 150; i < 200; i++) tiles[i][172].init(&tileset, i, 172);
	for (int i = 150; i < 200; i++) tiles[i][171].init(&tileset, i, 171);
	for (int i = 150; i < 200; i++) tiles[i][170].init(&tileset, i, 170);
	
	for (int i = 175; i < 200; i++) tiles[i][169].init(&tileset, i, 169);
	for (int i = 175; i < 200; i++) tiles[i][168].init(&tileset, i, 168);
	for (int i = 175; i < 200; i++) tiles[i][167].init(&tileset, i, 167);
	for (int i = 175; i < 200; i++) tiles[i][166].init(&tileset, i, 166);
	for (int i = 175; i < 200; i++) tiles[i][165].init(&tileset, i, 165);

	for (int i = 185; i < 200; i++) tiles[i][164].init(&tileset, i, 164);
	for (int i = 185; i < 200; i++) tiles[i][163].init(&tileset, i, 163);
	for (int i = 185; i < 200; i++) tiles[i][162].init(&tileset, i, 162);
	for (int i = 185; i < 200; i++) tiles[i][161].init(&tileset, i, 161);
	for (int i = 185; i < 200; i++) tiles[i][160].init(&tileset, i, 160);
	for (int i = 185; i < 200; i++) tiles[i][159].init(&tileset, i, 159);

	for (int i = 195; i < 200; i++) tiles[i][158].init(&tileset, i, 158);
	for (int i = 195; i < 200; i++) tiles[i][157].init(&tileset, i, 157);
	for (int i = 195; i < 200; i++) tiles[i][156].init(&tileset, i, 156);
	for (int i = 195; i < 200; i++) tiles[i][155].init(&tileset, i, 155);
	for (int i = 195; i < 200; i++) tiles[i][154].init(&tileset, i, 154);
	for (int i = 195; i < 200; i++) tiles[i][153].init(&tileset, i, 153);
	for (int i = 195; i < 200; i++) tiles[i][152].init(&tileset, i, 152);

	initPhys();
}



void fired::Map::deinit() {
	tileset.deinit();
}



void fired::Map::update() {
	sf::Vector2f offset = cam->getOffset();

	bgSprite->setPosition(offset);
	bgSprite->setTextureRect(sf::IntRect(offset.x / 2, offset.y / 2, settings->window.width, settings->window.height));

	render();
}



void fired::Map::render() {
	app->draw(*bgSprite);

	sf::Vector2i from((int)(cam->getOffset().x / TILE_SIZE), (int)(cam->getOffset().y / TILE_SIZE));
	sf::Vector2i to(from + visibleTiles);

	if (from.x < 0) from.x = 0;
	if (from.y < 0) from.y = 0;
	if (to.x > 200) to.x = 200;
	if (to.y > 200) to.y = 200;

	for (int i = from.x; i < to.x; i++)
		for (int j = from.y; j < to.y; j++)
			tiles[i][j].render(app);
}



void fired::Map::initPhys() {
	b2BodyDef      bodyDef;
	b2PolygonShape shapeDef;
	b2FixtureDef   fixtureDef;

	bodyDef.type = b2_staticBody;
	shapeDef.SetAsBox(toPhys(TILE_SIZE / 2), toPhys(TILE_SIZE / 2));
	fixtureDef.density = 0.f;
	fixtureDef.shape = &shapeDef;

	for (int i = 0; i < 200; i++) for (int j = 0; j < 200; j++)
		if (tiles[i][j].isSolid()) {
			bodyDef.position = b2Vec2(toPhys(i * TILE_SIZE + TILE_SIZE/2), toPhys(j * TILE_SIZE + TILE_SIZE/2));
			b2Body* body = physWorld->CreateBody(&bodyDef);
			body->CreateFixture(&fixtureDef);
		}
}
