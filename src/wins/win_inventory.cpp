#include "game.hpp"

//======================================================================


fired::InventoryWindowItem::InventoryWindowItem(sf::Vector2f pos, fired::InventoryItem **_item) {
	item = _item;
	rect = sf::FloatRect(pos, sf::Vector2f(40.0f, 40.0f));
}

//======================================================================


void fired::InventoryWindowItem::render(sf::Sprite *spr, sf::Text *count) {
	spr->setPosition(rectCenter(rect));
	app->draw(*spr);

	if ( item == NULL) return;
	if (*item == NULL) return;

	(*item)->sprite->setPosition(rectCenter(rect));
	app->draw(*(*item)->sprite);

	if ((*item)->count > 1) {
		char objCount[16];
		snprintf(objCount, sizeof(objCount), "%u", (*item)->count);

		count->setString(sf::String(objCount));
		count->setPosition(sf::Vector2f(rect.left + rect.width  - count->getGlobalBounds().width  - 7,
		                                rect.top  + rect.height - count->getGlobalBounds().height - 7));
		app->draw(*count);
	}
}

//======================================================================


fired::InventoryWindow::InventoryWindow(fired::Character *_owner) {
	owner  = _owner;
	win    = new fired::Window(sf::Vector2f(450, 500));
	inHand = new fired::InventoryWindowItem(sf::Vector2f(0.0f, 0.0f), NULL);

	emptyTex = new sf::Texture();
	hoverTex = new sf::Texture();
	normalTex = new sf::Texture();

	emptyTex->loadFromFile("data/img/gui/inventory/empty.tga");
	hoverTex->loadFromFile("data/img/gui/inventory/hover.tga");
	normalTex->loadFromFile("data/img/gui/inventory/normal.tga");

	emptySpr = new sf::Sprite();
	hoverSpr = new sf::Sprite();
	normalSpr = new sf::Sprite();

	emptySpr->setTexture(*emptyTex);
	hoverSpr->setTexture(*hoverTex);
	normalSpr->setTexture(*normalTex);

	emptySpr->setOrigin(sf::Vector2f(emptyTex->getSize())   / 2.0f);
	hoverSpr->setOrigin(sf::Vector2f(hoverTex->getSize())   / 2.0f);
	normalSpr->setOrigin(sf::Vector2f(normalTex->getSize()) / 2.0f);

	moneyText = new sf::Text();
	moneyText->setFont(*game->getFont());
	moneyText->setCharacterSize(16);
	moneyText->setPosition(win->getOffset() + sf::Vector2f(40.0f, 480.0f));
	moneyText->setColor(sf::Color::White);

	countText = new sf::Text();
	countText->setFont(*game->getFont());
	countText->setCharacterSize(12);
	countText->setColor(sf::Color::White);

	items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(205.0f,  25.0f), NULL)); //Helm
	items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(205.0f,  85.0f), NULL)); //Body
	items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(155.0f,  45.0f), NULL)); //Arms
	items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(155.0f, 125.0f), NULL)); //Fist
	items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(255.0f,  45.0f), NULL)); //Legs
	items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(255.0f, 125.0f), NULL)); //Shoe
	items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(180.0f, 185.0f), NULL)); //Prim
	items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(230.0f, 185.0f), NULL)); //Sec


	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(25.0f + 40.0f * i, 275.0f + 40.0f * j), &owner->inventory->items[i][j]));
}

//======================================================================


fired::InventoryWindow::~InventoryWindow() {
	delete win;
	delete moneyText;
	delete countText;

	delete emptySpr;
	delete hoverSpr;
	delete normalSpr;

	delete emptyTex;
	delete hoverTex;
	delete normalTex;

	deleteList(items);
}

//======================================================================


void fired::InventoryWindow::update(sf::Vector2f mousePos) {
	for (unsigned int i = 0; i < items.size(); i++)
		if (items[i]->rect.contains(mousePos)) items[i]->hover = true;
		else                                   items[i]->hover = false;

	render();
}

//======================================================================


void fired::InventoryWindow::render() {
	win->render();

	for (unsigned int i = 0; i < items.size(); i++)
		if      ( items[i]->hover)        items[i]->render(hoverSpr, countText);
		else if ( items[i]->item == NULL) items[i]->render(emptySpr, countText);
		else if (*items[i]->item == NULL) items[i]->render(emptySpr, countText);
		else                              items[i]->render(normalSpr, countText);


	owner->inventory->credits->sprite->setPosition(win->getOffset() + sf::Vector2f(30.0f, 490.0f));
	app->draw(*owner->inventory->credits->sprite);

	char credits[16];
	snprintf(credits, sizeof(credits), "%u", owner->inventory->credits->count);
	moneyText->setString(sf::String(credits));
	app->draw(*moneyText);
}

//======================================================================


void fired::InventoryWindow::click(sf::Vector2f mousePos) {
	return;
}

