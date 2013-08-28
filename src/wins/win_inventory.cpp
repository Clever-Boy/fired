#include "game.hpp"

//======================================================================


fired::InventoryWindowItem::InventoryWindowItem(sf::Vector2f pos, fired::InventoryItem **_item) {
	item = _item;
	rect = sf::FloatRect(pos, sf::Vector2f(35.0f, 35.0f));
}

//======================================================================


void fired::InventoryWindowItem::render(sf::Sprite *spr, sf::Text *count) {
	spr->setPosition(rectCenter(rect));
	app->draw(*spr);

	renderItem(count);
}

//======================================================================


void fired::InventoryWindowItem::renderItem(sf::Text *count) {
	if ( item == NULL) return;
	if (*item == NULL) return;

	(*item)->sprite->setPosition(rectCenter(rect));
	(*item)->sprite->setRotation(0.0f);
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
	win    = new fired::Window(sf::Vector2f(370, 380));
	inHand = new fired::InventoryWindowItem(sf::Vector2f(0.0f, 0.0f), new fired::InventoryItem*);
	*(inHand->item) = NULL;

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
	moneyText->setPosition(win->getOffset() + sf::Vector2f(30.0f, 360.0f));
	moneyText->setColor(sf::Color::White);

	countText = new sf::Text();
	countText->setFont(*game->getFont());
	countText->setCharacterSize(12);
	countText->setColor(sf::Color::White);

	items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(175.0f,  10.0f), &owner->inventory->helm));
	items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(175.0f,  65.0f), &owner->inventory->body));
	items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(130.0f,  22.0f), &owner->inventory->arms));
	items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(130.0f,  85.0f), &owner->inventory->fist));
	items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(220.0f,  25.0f), &owner->inventory->legs));
	items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(220.0f,  85.0f), &owner->inventory->shoe));

	items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(155.0f, 130.0f), &owner->inventory->primaryWeapon));
	items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(195.0f, 130.0f), &owner->inventory->secondaryWeapon));


	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			items.push_back(new fired::InventoryWindowItem(win->getOffset() + sf::Vector2f(10.0f + 35.0f * i, 185.0f + 35.0f * j), &owner->inventory->items[i][j]));
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

	inHand->rect.left = mousePos.x + 16.0f;
	inHand->rect.top  = mousePos.y + 16.0f;

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


	owner->inventory->credits->sprite->setPosition(win->getOffset() + sf::Vector2f(20.0f, 370.0f));
	app->draw(*owner->inventory->credits->sprite);

	char credits[16];
	snprintf(credits, sizeof(credits), "%u", owner->inventory->credits->count);
	moneyText->setString(sf::String(credits));
	app->draw(*moneyText);

	inHand->renderItem(countText);

}

//======================================================================


void fired::InventoryWindow::click(sf::Vector2f mousePos) {
	fired::InventoryWindowItem *selected = NULL;

	for (unsigned int i = 0; i < items.size(); i++)
		if (items[i]->rect.contains(mousePos)) {
			selected = items[i];
			break;
		}

	if (selected       == NULL) return;
	if (selected->item == NULL) return;


	if (*inHand->item == NULL) {
		if (*selected->item == NULL) return;

		*inHand->item   = *selected->item;
		*selected->item = NULL;
		return;
	} else if (*selected->item == NULL) {
		*selected->item = *inHand->item;
		*inHand->item   = NULL;
	} else {
		if ((*selected->item)->type == (*inHand->item)->type && !strcmp((*selected->item)->caption, (*inHand->item)->caption)) {
			(*selected->item)->count += (*inHand->item)->count;

			delete (*inHand->item);
			*inHand->item = NULL;
		} else {
			fired::InventoryItem *tmp;

			tmp = *selected->item;
			*selected->item = *inHand->item;
			*inHand->item   = tmp;
		}
	}
}

