#include "game.hpp"

void fired::MainMenu::Init(fired::Game *game) {
	BackgroundImage.LoadFromFile("data/img/gui/mainmenu/bg.jpg");
	MenuItemImage.LoadFromFile("data/img/gui/mainmenu/menuitem.jpg");
	LogoImage.LoadFromFile("data/img/gui/mainmenu/logo.tga");

	BackgroundSprite.SetImage(BackgroundImage);
	MenuItemSprite.SetImage(MenuItemImage);
	LogoSprite.SetImage(LogoImage);

	Game = game;

	MenuItem.Init();
	return;
}


void fired::MainMenu::Update(float FrameClock) {
	Render();
	return;
}


void fired::MainMenu::Render() {
	Game->App.Draw(BackgroundSprite);
}
