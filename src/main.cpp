#include <SFML/Graphics.hpp>
#include "events.hpp"

int main() {
	// After take the settings from config file (resolution and fullscreen)
	sf::RenderWindow App(sf::VideoMode(1024, 600, 32), "Name get from define", sf::Style::Fullscreen);
	sf::Event Event;

	while(App.IsOpened()) {
		while (App.GetEvent(Event)) ProcessEvent(Event);

		App.Clear();
		App.Display();
	}

	return EXIT_SUCCESS;
}
