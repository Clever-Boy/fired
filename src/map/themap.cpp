#include "game.hpp"

//======================================================================


void fired::Map::init(fired::Game *_game, fired::Camera *_cam) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	cam      = _cam;

	bgTex    = new sf::Texture();
	bgSprite = new sf::RectangleShape();

	bgTex->loadFromFile("data/img/bg/sky.jpg");
	bgSprite->setTexture(bgTex);
	bgTex->setRepeated(true);
	bgSprite->setSize(sf::Vector2f(settings->window.width, settings->window.height));

	tileset.init("data/img/tilesets/dirt.tga");

	visibleTiles.x = settings->window.width  / TILE_SIZE + 2;
	visibleTiles.y = settings->window.height / TILE_SIZE + 2;

	sizeX = 200;
	sizeY = 200;

	tiles = new fired::Tile*[sizeX];
	for (int i = 0; i < sizeX; i++)
		tiles[i] = new fired::Tile[sizeY];


	for (int i = 0; i < sizeX; i++) for (int j = 0; j < sizeY; j++)
		tiles[i][j].init(NULL, i, j);


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
}

//======================================================================


void fired::Map::deinit() {
	tileset.deinit();
	for (int i = 0; i < sizeX; i++)
		delete tiles[i];

	delete tiles;
}

//======================================================================


void fired::Map::update() {
	sf::Vector2f offset = cam->getOffset();

	bgSprite->setPosition(offset);
	bgSprite->setTextureRect(sf::IntRect(offset.x / 2, offset.y / 2, settings->window.width, settings->window.height));

	render();
}

//======================================================================


void fired::Map::render() {
	app->draw(*bgSprite);

	sf::Vector2i from((int)(cam->getOffset().x / TILE_SIZE), (int)(cam->getOffset().y / TILE_SIZE));
	sf::Vector2i to(from + visibleTiles);

	if (from.x < 0  ) from.x = 0;
	if (from.y < 0  ) from.y = 0;
	if (to.x > sizeX) to.x = sizeX;
	if (to.y > sizeY) to.y = sizeY;

	for (int i = from.x; i < to.x; i++)
		for (int j = from.y; j < to.y; j++)
			tiles[i][j].render(app);
}

//======================================================================


void checkCollision(fired::Phys *phys, int tile_x, int tile_y) {
	sf::FloatRect intersection;

	if (phys->rect.intersects(sf::FloatRect(tile_x * TILE_SIZE, tile_y * TILE_SIZE, TILE_SIZE, TILE_SIZE), intersection)) {
		if (intersection.width > intersection.height) {
			if (phys->pos.y < tile_y * TILE_SIZE) {
				phys->pos.y -= intersection.height;
				if (phys->velocity.y > 0.0) phys->velocity.y = 0.0;
				phys->onGround = true;
			} else {
				phys->pos.y += intersection.height;
				if (phys->velocity.y < 0.0) phys->velocity.y = 0.0;
			}
		} else {
			if (phys->pos.x < tile_x * TILE_SIZE) {
				phys->pos.x -= intersection.width;
				if (phys->velocity.x > 0.0) phys->velocity.x = 0.0;
				phys->isMoving = false;
			} else {
				phys->pos.x += intersection.width;
				if (phys->velocity.x < 0.0) phys->velocity.x = 0.0;
				phys->isMoving = false;
			}
		}

		phys->rect = sf::FloatRect(phys->pos, phys->size);
	}
}

//======================================================================


void fired::Map::checkPhys(fired::Phys *phys) {
	int i, j;

	phys->onGround = false;

	if (phys->velocity.x > PHYS_MAX_FALL) phys->velocity.x = PHYS_MAX_FALL;
	if (phys->velocity.y > PHYS_MAX_FALL) phys->velocity.y = PHYS_MAX_FALL;

	float frameLeft = frameClock;
	float frameChunk;
	float velocity = sqrt(sqr(phys->velocity.x + phys->acceleration.x * frameClock) + sqr(phys->velocity.y + phys->acceleration.y * frameClock));

	if (velocity == 0.0)
		frameChunk = frameClock;
	else
		frameChunk = PHYS_TUNNEL_CHUNK / velocity;


	while (frameLeft > 0.0) {
		if (frameChunk > frameLeft) frameChunk = frameLeft;

		phys->velocity += phys->acceleration * frameChunk;
		phys->pos += phys->velocity * frameChunk;
		phys->rect = sf::FloatRect(phys->pos, phys->size);

		sf::Vector2i  tiles_from((int)(phys->pos.x / TILE_SIZE), (int)(phys->pos.y / TILE_SIZE));
		sf::Vector2i  tiles_to((int)((phys->pos.x + phys->size.x) / TILE_SIZE), (int)((phys->pos.y + phys->size.y) / TILE_SIZE));


		for (i = tiles_from.x + 1; i <= tiles_to.x - 1; i++) {
			if (tiles[i][tiles_from.y].isSolid()) checkCollision(phys, i, tiles_from.y);
			if (tiles[i][tiles_to.y].isSolid()) checkCollision(phys, i, tiles_to.y);
		}

		for (j = tiles_from.y + 1; j <= tiles_to.y - 1; j++) {
			if (tiles[tiles_from.x][j].isSolid()) checkCollision(phys, tiles_from.x, j);
			if (tiles[tiles_to.x][j].isSolid()) checkCollision(phys, tiles_to.x, j);
		}

		if (phys->velocity.x > 0) {
			if (tiles[tiles_from.x][tiles_from.y].isSolid()) checkCollision(phys, tiles_from.x, tiles_from.y);
			if (tiles[tiles_from.x][tiles_to.y  ].isSolid()) checkCollision(phys, tiles_from.x, tiles_to.y  );
			if (tiles[tiles_to.x  ][tiles_from.y].isSolid()) checkCollision(phys, tiles_to.x  , tiles_from.y);
			if (tiles[tiles_to.x  ][tiles_to.y  ].isSolid()) checkCollision(phys, tiles_to.x  , tiles_to.y  );
		} else {
			if (tiles[tiles_to.x  ][tiles_from.y].isSolid()) checkCollision(phys, tiles_to.x  , tiles_from.y);
			if (tiles[tiles_to.x  ][tiles_to.y  ].isSolid()) checkCollision(phys, tiles_to.x  , tiles_to.y  );
			if (tiles[tiles_from.x][tiles_from.y].isSolid()) checkCollision(phys, tiles_from.x, tiles_from.y);
			if (tiles[tiles_from.x][tiles_to.y  ].isSolid()) checkCollision(phys, tiles_from.x, tiles_to.y  );
		}

		frameLeft -= frameChunk;
	}
}
